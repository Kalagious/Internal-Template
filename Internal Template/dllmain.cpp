#include "general.h"

DWORD APIENTRY CheatThread(HMODULE hModule)
{
    // Open a console window for debug output
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    SetConsoleTitleA("Cheat Debug");

    mainCode(hModule);

    FreeConsole();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
#pragma warning(disable: 6387)
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CheatThread, hModule, NULL, NULL));
#pragma warning(default: 6387)
    return TRUE;
}
