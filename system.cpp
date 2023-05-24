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

    // Get system information
    std::time_t currentTime = std::time(nullptr);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), std::localtime(&currentTime));


    // Write system information to the file
    outputFile << "System Information" << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "Username: " << WindowsUsername << std::endl;
    outputFile << "Date and Time: " << std::asctime(std::localtime(&currentTime));
    outputFile << "Computer Name: " << ComputerName << std::endl;
    outputFile << "Windows Version: " << osver << std::endl;
    // Next update is:
//    outputFile << "Build Number: " << osVersionInfo.dwBuildNumber << std::endl;

    // Close the file
    outputFile.close();

    std::cout << "System information saved to " << filename << " successfully." << std::endl;
}

void GetThatSystemInfo(std::string ComputerName,int osver,std::string WindowsUsername) {
    std::string filename = "system_info.txt";
    saveSystemInfoToFile(filename,ComputerName,osver,WindowsUsername);
}

