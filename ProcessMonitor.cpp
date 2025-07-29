#include "ProcessMonitor.h"
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

std::vector<Process> ProcessMonitor::fetchAll() {
    std::vector<Process> processes;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return processes;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pe)) {
        do {
            DWORD pid = pe.th32ProcessID;
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

            double memoryMB = 0.0;
            if (hProcess) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    memoryMB = pmc.WorkingSetSize / 1024.0;
                }
                CloseHandle(hProcess);
            }

            Process proc(pid, QString::fromWCharArray(pe.szExeFile), 0.0, memoryMB);
            processes.push_back(proc);

        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return processes;
}