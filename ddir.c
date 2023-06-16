#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "debug.h"
#include "tree.h"



void GetDDir() {
    debout("D Tree", 2, "Running");
    FILE* file;
    errno_t err = fopen_s(&file, "d.txt", "w");
    if (err != 0) {
        printf("Failed to open file.\n");
        return;
    }

    const char* path = "D:\\";

    fprintf(file, "%s\n", path);
    printTree(path, 0, file);

    fclose(file);
    debout("D Tree", 2, "Done");
}