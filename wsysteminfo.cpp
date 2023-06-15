#define _CRT_SECURE_NO_WARNINGS
#include "debug.h"
#include "writer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void saveSystemInfoToFile(
    const std::string& filename,
    std::string ComputerName,
    double osver, std::string WindowsUsername,
    std::string BuildNum,
    std::string WinVer,
    std::string ProcName,
    std::string TotalMem,
    std::string gpuName,
    int diskcount,
    int partcount,
    int intercount,
    std::string internames,
    std::string diskoname,
    double diskosize,
    std::string diskiname,
    double diskisize
) {
    // Open the output file
    debout("Writing Systeminfo", 2, "Starting Writing");
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
    outputFile << "Total Disk: " << diskcount << std::endl;
    outputFile << "Total Partition: " << partcount << std::endl;
    outputFile << "GPU: " << gpuName << std::endl;
    outputFile << "Interface Count: " << intercount << std::endl;
    outputFile << "Interface List: " << std::endl << internames << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "       Disk 0     " << std::endl;
    outputFile << "------------------" << std::endl;
    outputFile << "Name: " << diskoname << std::endl;
    outputFile << "Size: " << diskosize << " GB" << std::endl;
    if (diskcount == 2)
    {
        outputFile << "------------------" << std::endl;
        outputFile << "       Disk 1     " << std::endl;
        outputFile << "------------------" << std::endl;
        outputFile << "Name: " << diskiname << std::endl;
        outputFile << "Size: " << diskisize << " GB" << std::endl;
    }
    
    // Close the file
    outputFile.close();
    debout("Systeminfo", 1,"Done Writing");
}
