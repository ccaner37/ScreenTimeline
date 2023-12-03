#include <stdio.h>

#include <string.h>
#include <windows.h>
#include <iostream>
#include <string>

#include <Psapi.h>

using namespace std;

int main() 
{
	Sleep(1000);
	char windowTitle[256];
	HWND foregroundWindow = GetForegroundWindow();
	TCHAR szName[MAX_PATH];
	
	//LPDWORD id;


	//GetWindowTextW(foregroundWindow, windowTitle, sizeof(windowTitle));
	
	//GetWindowThreadProcessId(foregroundWindow, id);

	DWORD processID;
	GetWindowThreadProcessId(foregroundWindow, &processID);
	cout << processID;
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (processHandle == NULL) 
	{

		cout << std::system_category().message(GetLastError());;
	}

	cout << "  err:  " << GetLastError();

	GetModuleBaseNameA(processHandle, NULL, windowTitle, MAX_PATH);

	cout << "  err:  " << GetLastError();

	wstring ws(szName);
	string str(ws.begin(), ws.end());

	cout << "  -  " << windowTitle;
}