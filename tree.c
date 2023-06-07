#include "connect.h"
#include "tree.h"
#include <stdio.h>
#include <Windows.h>
//sometimes work sometimes didn't

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
