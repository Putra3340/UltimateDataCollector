#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
#include "connect.h"
#include "cpp.h"
#include <ctime>
#include <Windows.h>
#include <lmcons.h>
using namespace std;

//same code like from my repo PassManager/panel.cpp

void DetailedComputerInfo() {
	HKEY hKey;
	DWORD dwType, dwSize;
	char szBuildNumber[50];

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		dwSize = sizeof(szBuildNumber);
		if (RegQueryValueExA(hKey, "BuildLabEx", NULL, &dwType, reinterpret_cast<LPBYTE>(szBuildNumber), &dwSize) == ERROR_SUCCESS) {
			if (dwType == REG_SZ) {
			}
		}
	}
	int osver = 0.0;

	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);

	OSVERSIONINFOEXW osInfo;

	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

	if (NULL != RtlGetVersion)
	{
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		RtlGetVersion(&osInfo);
		osver = osInfo.dwMajorVersion;
	}

	char username[UNLEN + 1]; //user
	DWORD username_len = UNLEN + 1;
	GetUserNameA(username, &username_len);


	char computerName[MAX_COMPUTERNAME_LENGTH + 1]; //comname
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	if (GetComputerNameA(computerName, &size)) {



		std::cout << "Computer name: " << computerName << std::endl;
		std::cout << "Current OS : Windows " << osver << endl; //osver
		std::cout << "Username: " << username << std::endl;
		std::cout << szBuildNumber;
		GetThatSystemInfo(computerName, osver, username,szBuildNumber);
	}
	
}