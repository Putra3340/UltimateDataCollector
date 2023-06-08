#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
#include "connect.h"
#include <ctime>
#include <Windows.h>
#include <lmcons.h>
#include "writer.h"
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
using namespace std;


//same code like from my repo PassManager/panel.cpp
//after 2 week i just know that i can grab from regedit bruh...


void DetailedComputerInfo() {
	HKEY hKey;
	DWORD dwType, dwSize;

	// Build Number from regedit
	char szBuildNumber[50];
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);
	dwSize = sizeof(szBuildNumber);
	RegQueryValueExA(hKey, "BuildLabEx", NULL, &dwType, reinterpret_cast<LPBYTE>(szBuildNumber), &dwSize);

	// New get windows ver
	char szWindowsVersion[50];
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);
	dwSize = sizeof(szWindowsVersion);
	RegQueryValueExA(hKey, "ProductName", NULL, &dwType, reinterpret_cast<LPBYTE>(szWindowsVersion), &dwSize);
	
	// get CPU
	char szProcessorName[75];
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	dwSize = sizeof(szProcessorName);
	RegQueryValueExA(hKey, "ProcessorNameString", NULL, &dwType, reinterpret_cast<LPBYTE>(szProcessorName), &dwSize);
	
	// get ram total
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(memInfo);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalMem = memInfo.ullTotalPhys;
	DWORDLONG totalMemoryMB = totalMem / (1024 * 1024);
	std::string totalram = std::to_string(totalMemoryMB);

	// get gpu?
	IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DADAPTER_IDENTIFIER9 adapterInfo;
	d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapterInfo);
	std::string gpuName = adapterInfo.Description;
	d3d->Release();

	// get windows ver...old but im still using it
	double osver = 0.0;
	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osInfo;
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");
	if (NULL != RtlGetVersion){
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		RtlGetVersion(&osInfo);
		osver = osInfo.dwMajorVersion;}

	// get windows username ez af
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(username, &username_len);

	// get computer name
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	if (GetComputerNameA(computerName, &size)) {
		// idk when i put computerName var out of if condition its fucking bugged
		std::string sysfilename = "system_info.txt";
		// System Information
		std::cout << computerName << std::endl; 
		std::cout << osver << endl;
		std::cout << username << std::endl;
		std::cout << szBuildNumber;
		std::cout << szWindowsVersion;
		std::cout << szProcessorName;
		std::cout << totalram;
		std::cout << gpuName;
		saveSystemInfoToFile(sysfilename,computerName, osver, username,szBuildNumber,szWindowsVersion,szProcessorName,totalram,gpuName);
	}
	
}