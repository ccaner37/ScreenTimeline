#include <iostream>
#include "ScreenTimeline.h"
#include "WindowsHelper.h"
#include <map>

using namespace std;

int main() {

    map<string, int> timeMap;

    WindowsHelper windowsHelper;

    while (true)
    {
        Sleep(1000);

        windowsHelper.WarnForegroundWindowDescription();
    }
}