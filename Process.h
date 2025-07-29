#pragma once
#include <QString>

class Process {
public:
    // Construtor
    Process(int pid, QString name, double cpuUsage = 0.0, double memoryUsage = 0.0);

    // Métodos de acesso
    [[nodiscard]] auto pid() const -> int;
    [[nodiscard]] QString name() const;
    [[nodiscard]] double cpuUsage() const;
    [[nodiscard]] double memoryUsage() const;

private:
    // Atributos privados
    int m_pid;
    QString m_name;
    double m_cpuUsage;
    double m_memoryUsage;
};
