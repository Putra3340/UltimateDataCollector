#include "writerc.h"
#include <stdio.h>

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