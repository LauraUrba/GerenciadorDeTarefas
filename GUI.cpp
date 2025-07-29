#include "GUI.h"
#include "ProcessMonitor.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <windows.h>

GUI::GUI(QWidget* parent) : QMainWindow(parent) {
    setupUI();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &GUI::updateProcessList);
    refreshTimer->start(3000); // Atualiza a cada 3 segundos

    updateProcessList(); // Chama inicialmente
}

GUI::~GUI() = default;

void GUI::setupUI() {
    setWindowTitle("Gerenciador de Tarefas");
    resize(800, 600);

    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);

    processTable = new QTableWidget(0, 4, this);
    processTable->setHorizontalHeaderLabels({"PID", "Nome", "Uso de CPU (%)", "Uso de Memória (MB)"});
    processTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    processTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    processTable->setSelectionMode(QAbstractItemView::SingleSelection);

    refreshButton = new QPushButton("Atualizar");
    terminateButton = new QPushButton("Finalizar Processo");

    layout->addWidget(processTable);
    layout->addWidget(refreshButton);
    layout->addWidget(terminateButton);

    connect(refreshButton, &QPushButton::clicked, this, &GUI::updateProcessList);
    connect(terminateButton, &QPushButton::clicked, this, &GUI::terminateSelectedProcess);

    setCentralWidget(centralWidget);
}



void GUI::updateProcessList() {
    auto processos = ProcessMonitor::fetchAll();
    populateTable(QVector<Process>(processos.begin(), processos.end()));
}



void GUI::populateTable(const QVector<Process>& processes) {
    processTable->setRowCount(0);

    for (const auto& p : processes) {
        int row = processTable->rowCount();
        processTable->insertRow(row);
        processTable->setItem(row, 0, new QTableWidgetItem(QString::number(p.pid())));
        processTable->setItem(row, 1, new QTableWidgetItem(p.name()));
        processTable->setItem(row, 2, new QTableWidgetItem(QString::number(p.cpuUsage(), 'f', 2)));
        processTable->setItem(row, 3, new QTableWidgetItem(QString::number(p.memoryUsage(), 'f', 2)));
    }
}

void GUI::terminateSelectedProcess() {
    auto items = processTable->selectedItems();
    if (items.empty()) return;

    int row = processTable->row(items[0]);
    int pid = processTable->item(row, 0)->text().toInt();

    // 🔒 Proteção contra autodestruição
    if (pid == GetCurrentProcessId()) {
        QMessageBox::warning(this, "Atenção", "Você está tentando finalizar o próprio gerenciador!");
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess) {
        QMessageBox::warning(this, "Erro", "Não foi possível abrir o processo.");
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        QMessageBox::information(this, "Sucesso", "Processo finalizado com sucesso.");
        updateProcessList();
    } else {
        DWORD errorCode = GetLastError();
        QMessageBox::critical(this, "Erro", QString("Falha ao finalizar processo. Código de erro: %1").arg(errorCode));
    }

    CloseHandle(hProcess);
    if (TerminateProcess(hProcess, 0)) {
        updateProcessList(); // só atualiza se foi finalizado
    }
}