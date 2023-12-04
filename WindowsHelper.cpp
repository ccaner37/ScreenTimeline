#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <Psapi.h>

#include "WindowsHelper.h"
#include <functional>

BOOL WindowsHelper::GetFileDescription(std::string targetPath) {
    const char* filename = targetPath.c_str();
    int dwLen = GetFileVersionInfoSizeA(filename, NULL);
    if (!dwLen)
        return 0;

    auto* sKey = new BYTE[dwLen];
    std::unique_ptr<BYTE[]> skey_automatic_cleanup(sKey);
    if (!GetFileVersionInfoA(filename, NULL, dwLen, sKey))
        return 0;

    struct LANGANDCODEPAGE {
        WORD wLanguage;
        WORD wCodePage;
    } *lpTranslate;

    UINT cbTranslate = 0;
    if (!VerQueryValueA(sKey, "\\VarFileInfo\\Translation",
        (LPVOID*)&lpTranslate, &cbTranslate))
        return 0;

    for (unsigned int i = 0; i < (cbTranslate / sizeof(LANGANDCODEPAGE)); i++)
    {
        char subblock[256];
        //use sprintf if sprintf_s is not available
        sprintf_s(subblock, "\\StringFileInfo\\%04x%04x\\FileDescription",
            lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);
        char* description = NULL;
        UINT dwBytes;
        if (VerQueryValueA(sKey, subblock, (LPVOID*)&description, &dwBytes))
            MessageBoxA(0, description, 0, 0);
    }
    return TRUE;
}

string WindowsHelper::GetForegroundWindowFileName() {
    char fileName[256];
    HANDLE processHandle;
    GetForegroundWindowProcess(processHandle);
    GetModuleBaseNameA(processHandle, NULL, fileName, MAX_PATH);

    CloseHandle(processHandle);

    return fileName;
}

string WindowsHelper::GetForegroundWindowFilePath() {
    TCHAR path[MAX_PATH];
    HANDLE processHandle;
    GetForegroundWindowProcess(processHandle);
    GetModuleFileNameEx(processHandle, NULL, path, MAX_PATH);

    CloseHandle(processHandle);

    wstring wPath(path);
    string stringPath(wPath.begin(), wPath.end());
    return stringPath;
}

void WindowsHelper::WarnForegroundWindowDescription()
{
    GetFileDescription(GetForegroundWindowFilePath());
}

string WindowsHelper::GetForegroundWindowText() {
    //GetWindowTextW(foregroundWindow, windowTitle, sizeof(windowTitle));
    return "";
}

void WindowsHelper::GetForegroundWindowProcess(HANDLE &handle) {
    HWND foregroundWindow = GetForegroundWindow();
    DWORD processID;
    GetWindowThreadProcessId(foregroundWindow, &processID);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    handle = processHandle;
    //function<void(HANDLE)> callback = [](HANDLE handle) {
    //    CloseHandle(handle);
    //};
    //return callback;
}

void WindowsHelper::CloseProcess(HANDLE &process) {
    CloseHandle(process);
}
