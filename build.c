#include <windows.h>
#include <stdio.h>
#include <ntstatus.h>

// Trying to get Build Number but failed

typedef LONG NTSTATUS;
typedef struct _OSVERSIONINFOEXW {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    WCHAR szCSDVersion[128];
} OSVERSIONINFOEXW, * POSVERSIONINFOEXW;

NTSTATUS(WINAPI* RtlGetVersion)(POSVERSIONINFOEXW);

void GetBuildNumber() {
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (hNtdll != NULL) {
        RtlGetVersion = (NTSTATUS(WINAPI*)(POSVERSIONINFOEXW))GetProcAddress(hNtdll, "RtlGetVersion");
        if (RtlGetVersion != NULL) {
            OSVERSIONINFOEXW osvi;
            ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));
            osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

            if (RtlGetVersion(&osvi) == 0) {
                printf("OS Build Number: %lu\n", osvi.dwBuildNumber);
            }
            else {
                printf("Failed to retrieve OS version information.\n");
            }
        }
        else {
            printf("Failed to load RtlGetVersion function.\n");
        }
    }
    else {
        printf("Failed to load ntdll.dll.\n");
    }
}