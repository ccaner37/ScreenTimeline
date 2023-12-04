#pragma once

#include <stdio.h>
#include <string.h>
#include <windows.h>

using namespace std;

class WindowsHelper {
	public: 
		BOOL GetFileDescription(string targetPath);
		string GetForegroundWindowText();
		string GetForegroundWindowFileName();
		string GetForegroundWindowFilePath();
		void WarnForegroundWindowDescription();
	
	private:
		void GetForegroundWindowProcess(HANDLE &handle); // std::function<void(HANDLE)>
		void CloseProcess(HANDLE &process);
};