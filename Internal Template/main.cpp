#include "general.h"
#include "cheats.h"
// #include "SwapBuffersHook.h"  // uncomment when ready to enable OpenGL hook

Cheats* g_cheats = nullptr;
// SwapBuffersHook* g_swapHook = nullptr;

void mainCode(HMODULE hModule)
{
    LOG("mainCode: starting");

    g_cheats = new Cheats();

    // Main loop — runs until END key is pressed
    while (!g_cheats->uninject)
    {
        g_cheats->cheatUpdate();
    }

    g_cheats->cleanup();
    delete g_cheats;
    g_cheats = nullptr;

    LOG("mainCode: exiting");
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}
