#define _CRT_SECURE_NO_WARNINGS
#include "writer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void saveSystemInfoToFile(const std::string& filename, std::string ComputerName, int osver, std::string WindowsUsername, std::string BuildNum, std::string WinVer,std::string ProcName, std::string TotalMem,std::string gpuName) {
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

    // Write system information to the file
    outputFile << "------------------" << std::endl;
    outputFile << "System Information" << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "Username: " << WindowsUsername << std::endl;
    outputFile << "Date and Time: " << std::asctime(std::localtime(&currentTime));
    outputFile << "Computer Name: " << ComputerName << std::endl;
    outputFile << "Windows Version: " << WinVer << " (" << osver << ")" << std::endl;
    outputFile << "Build Number: " << BuildNum << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "       Specs      " << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "Processor Name: " << ProcName << std::endl;
    outputFile << "Memory: " << TotalMem << std::endl;
    outputFile << "GPU: " << gpuName << std::endl;
    // Close the file
    outputFile.close();
}
