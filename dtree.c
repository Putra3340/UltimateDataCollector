#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void GetDDir() {
    // Bugged
    // Open the file for writing
    FILE* file;
    errno_t err = fopen_s(&file, "d.txt", "w");
    if (err != 0) {
        printf("Failed to open file.\n");
        
    }

    // Create the command to execute
    char command[] = "cmd /c tree /A D:\\";

    // Create a pipe to capture the output of the command
    FILE* pipe = _popen(command, "r");
    if (pipe == NULL) {
        printf("Failed to execute the command.\n");
        
    }

    // Read the output of the command and write it to the file
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        fputs(buffer, file);
    }

    // Close the pipe and the file
    _pclose(pipe);
    fclose(file);

    printf("Directory tree has been written to c.txt\n");
}
