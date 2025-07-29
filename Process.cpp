#include "Process.h"

#include <utility>

Process::Process(const int pid, QString  name, double cpuUsage, double memoryUsage)
    : m_pid(pid), m_name(std::move(name)), m_cpuUsage(cpuUsage), m_memoryUsage(memoryUsage) {}

int Process::pid() const {
    return m_pid;

}

QString Process::name() const {
    return m_name;
}

double Process::cpuUsage() const {
    return m_cpuUsage;
}

double Process::memoryUsage() const {
    return m_memoryUsage;
}

