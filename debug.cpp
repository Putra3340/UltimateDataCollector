#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "debug.h"

void debout(const char* TaskName,double idk,const char* info) {
    // Set General
    const std::string blueColor = "\033[1;34m";
    const std::string yellowColor = "\033[33m";
    const std::string redColor = "\033[1;31m";
    const std::string boldFont = "\033[1m";
    const std::string resetFormat = "\033[0m";
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* localTime = std::localtime(&currentTimeT);
    int hours = localTime->tm_hour;
    int minutes = localTime->tm_min;
    int seconds = localTime->tm_sec;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count() % 1000;
    std::string clock = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milliseconds);

    if (idk == 1)
    {
        std::cout << "[" << clock << "]" << "[" << blueColor << boldFont << "Info" << resetFormat << "] Task " << TaskName << " : " << info << std::endl;
    }
    if (idk == 2) {
        std::cout << "[" << clock << "]" << "[" << yellowColor << boldFont << "Warning" << resetFormat << "] Task " << TaskName << " : " << info << std::endl;
    }
    if (idk == 3)
    {
        std::cout << "[" << clock << "]" << "[" << redColor << boldFont << "ERROR" << resetFormat << "] Task " << TaskName << " : " << info << std::endl;
    }
}