#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include "connect.h"
// The logs write update every 1 sec

void GetProcessName(DWORD processId, LPWSTR processName, DWORD bufferSize)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess != NULL)
    {
        if (QueryFullProcessImageNameW(hProcess, 0, processName, &bufferSize) == 0)
        {
            processName[0] = L'\0';
        }

        CloseHandle(hProcess);
    }
}

void LogProgram(const char* programName)
{
    FILE* logFile;
    if (fopen_s(&logFile, "program_log.txt", "a") == 0)
    {
        fprintf(logFile, "%s\n", programName);
        fclose(logFile);
    }
    else
    {
        fprintf(stderr, "Error opening log file.\n");
    }
}

void GetProcessInfo()
{
    char previousProgram[MAX_PATH] = "";

    while (1)
    {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32 processEntry;
            processEntry.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(hSnapshot, &processEntry))
            {
                do
                {
                    DWORD processId = processEntry.th32ProcessID;
                    WCHAR processName[MAX_PATH];
                    GetProcessName(processId, processName, MAX_PATH);

                    char currentProgram[MAX_PATH];
                    if (WideCharToMultiByte(CP_UTF8, 0, processName, -1, currentProgram, MAX_PATH, NULL, NULL) != 0)
                    {
                        if (strcmp(currentProgram, previousProgram) != 0)
                        {
                            strcpy_s(previousProgram, MAX_PATH, currentProgram);
                            LogProgram(currentProgram);
                        }
                    }
                } while (Process32Next(hSnapshot, &processEntry));
            }

            CloseHandle(hSnapshot);
        }

        Sleep(1000);
    }
}
