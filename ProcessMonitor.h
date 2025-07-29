#pragma once
#include <vector>
#include "Process.h"

class ProcessMonitor {
public:
    static std::vector<Process> fetchAll();

    void fetchProcesses() {
    }
};