#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
#include "connect.h"
#include <locale>
#include <codecvt>
#include <ctime>
#include <Windows.h>
#include <lmcons.h>
#include <vector>
#include "writer.h"
#include <d3d9.h>
#include <comdef.h>
#include <WbemIdl.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "d3d9.lib")
using namespace std;


//same code like from my repo PassManager/panel.cpp
//after 2 week i just know that i can grab from regedit bruh...
//its hard at WMI

// convert Wstring to string
std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

void DetailedComputerInfo() {
	// How many disks
	// this is tough WMI ----------------------------------------------------------------------------------------------
	HRESULT hr;
    // Initialize COM
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed: " << std::hex << hr << std::endl;
    }

    // Initialize WMI
    hr = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );
    if (FAILED(hr)) {
        std::cerr << "WMI initialization failed: " << std::hex << hr << std::endl;
        CoUninitialize();
    }

    // Connect to WMI
    IWbemLocator* pLoc = NULL;
    hr = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );
    if (FAILED(hr)) {
        std::cerr << "Failed to create IWbemLocator instance: " << std::hex << hr << std::endl;
        CoUninitialize();
    }

    IWbemServices* pSvc = NULL;
    hr = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc
    );
    if (FAILED(hr)) {
        std::cerr << "Failed to connect to WMI server: " << std::hex << hr << std::endl;
        pLoc->Release();
        CoUninitialize();
    }

    // Query for physical disks
    IEnumWbemClassObject* pEnumerator = NULL;
    hr = pSvc->ExecQuery(
        _bstr_t("WQL"),
        _bstr_t("SELECT * FROM Win32_DiskDrive"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hr)) {
        std::cerr << "Query for physical disks failed: " << std::hex << hr << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }

    // Query Interface
    hr = pSvc->ExecQuery(
        _bstr_t("WQL"),
        _bstr_t("SELECT * FROM Win32_NetworkAdapter WHERE NetConnectionStatus = 2"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hr)) {
        std::cerr << "Query for network interfaces failed: " << std::hex << hr << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }

    ULONG uReturn = 0;
    int diskcount = 0;
    std::vector<std::wstring> interfaceNames;
    
    // Enumerate the all query results
    while (pEnumerator) {
        IWbemClassObject* pClsObj = NULL;
        hr = pEnumerator->Next(WBEM_INFINITE, 1, &pClsObj, &uReturn);
        if (0 == uReturn)
            break;

        VARIANT vtProp;
        hr = pClsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hr)) {
            diskcount++;
            std::wcout << L"Disk: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }
        hr = pClsObj->Get(L"NetConnectionID", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hr)) {
            interfaceNames.push_back(vtProp.bstrVal);
            VariantClear(&vtProp);
        }
        pClsObj->Release();
    }
    // WMI BORDER --------------------------------------------------------------------------------------------
    // Define from WMI
    size_t interfacecount = interfaceNames.size();
    int intcount = static_cast<int>(interfacecount);
    std::wstring intNames;
    for (const auto& name : interfaceNames) {
        intNames += name + L"\n";
    }
    std::string interNames = wstringToString(intNames);

	// How many partition
	DWORD drives = GetLogicalDrives();
	int partcount = 0;
	for (char letter = 'A'; letter <= 'Z'; letter++) {
		if (drives & 1) {
			partcount++;
		}
		drives >>= 1;
	}

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
        pEnumerator->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
		std::cout << computerName << std::endl; 
		std::cout << osver << endl;
		std::cout << username << std::endl;
		std::cout << szBuildNumber;
		std::cout << szWindowsVersion;
		std::cout << szProcessorName;
		std::cout << totalram;
		std::cout << gpuName;
		std::cout << diskcount;
        std::cout << interNames;
		saveSystemInfoToFile(sysfilename,computerName, osver, username,szBuildNumber,szWindowsVersion,szProcessorName,totalram,gpuName,diskcount,partcount,intcount,interNames);
	}
	
}