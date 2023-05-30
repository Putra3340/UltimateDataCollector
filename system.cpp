#define _CRT_SECURE_NO_WARNINGS
#include "connect.h"
#include "cpp.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <Windows.h>


void saveSystemInfoToFile(const std::string& filename,std::string ComputerName,int osver, std::string WindowsUsername) {
    // Open the output file
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }

    // Get current time
    std::time_t currentTime = std::time(nullptr);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), std::localtime(&currentTime));

    // get build number
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN10);
    osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN10);
    osvi.wServicePackMajor = 0;
    osvi.wServicePackMinor = 0;

    DWORDLONG conditionMask = 0;
    VER_SET_CONDITION(conditionMask, VER_MAJORVERSION, VER_EQUAL);
    VER_SET_CONDITION(conditionMask, VER_MINORVERSION, VER_EQUAL);
    VER_SET_CONDITION(conditionMask, VER_SERVICEPACKMAJOR, VER_EQUAL);
    VER_SET_CONDITION(conditionMask, VER_SERVICEPACKMINOR, VER_EQUAL);

    if (VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, conditionMask)) {
        // Display the build number
        std::cout << "Windows Build Number: " << osvi.dwBuildNumber << std::endl;
    }
    

    // Write system information to the file
    outputFile << "System Information" << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "Username: " << WindowsUsername << std::endl;
    outputFile << "Date and Time: " << std::asctime(std::localtime(&currentTime));
    outputFile << "Computer Name: " << ComputerName << std::endl;
    outputFile << "Windows Version: " << osver << std::endl;
    // Next update is:
    outputFile << "Build Number: " << osvi.dwBuildNumber << std::endl;

    // Close the file
    outputFile.close();

    std::cout << "System information saved to " << filename << " successfully." << std::endl;
}

void GetThatSystemInfo(std::string ComputerName,int osver,std::string WindowsUsername) {
    std::string filename = "system_info.txt";
    saveSystemInfoToFile(filename,ComputerName,osver,WindowsUsername);
}

