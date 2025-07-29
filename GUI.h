#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QTimer>

#include "Process.h"

class GUI final : public QMainWindow {
    Q_OBJECT

public:
    explicit GUI(QWidget* parent = nullptr);
    ~GUI() override;

private slots:
    void updateProcessList();

    void populateTable(const QVector<Process> &processes) const {
    }

    void terminateSelectedProcess();

private:
    void setupUI();
    /**
     *
     * @param processes
     */
    void populateTable(const QVector<Process> &processes);

    QTableWidget* processTable{};
    QPushButton* refreshButton{};
    QPushButton* terminateButton{};
    QTimer* refreshTimer{};
};
