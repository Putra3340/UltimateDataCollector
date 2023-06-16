#define _CRT_SECURE_NO_WARNINGS
#include "connect.h"
#include "tree.h"
#include <stdio.h>
#include <Windows.h>
//sometimes work sometimes didn't
void printTree(const char* path, int level, FILE* file) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    sprintf(searchPath, "%s\\*", path);
    hFind = FindFirstFileA(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(file, "Failed to open directory: %s\n", path);
        return;
    }

    char indent[256] = "";
    for (int i = 0; i < level; i++) {
        strcat(indent, "|   ");
    }

    do {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
            fprintf(file, "%s|-- %s\n", indent, findData.cFileName);

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                char nextPath[MAX_PATH];
                sprintf(nextPath, "%s\\%s", path, findData.cFileName);
                printTree(nextPath, level + 1, file);
            }
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}

void DirCheck() {
    UINT driveType = GetDriveType("D:\\");
    UINT driveEType = GetDriveType("E:\\");
    GetCDir();

    if (driveType == DRIVE_UNKNOWN) {
        printf("Drive D: does not exist.\n");
    }
    else {
        printf("Drive D: exists.\n");
        GetDDir();

    }
    if (driveEType == DRIVE_UNKNOWN) {
        printf("Drive E: does not exist.\n");
    }
    else {
        printf("Drive E: exists.\n");
        GetEDir();
    }
}
