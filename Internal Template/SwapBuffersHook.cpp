#include "SwapBuffersHook.h"
#include "gui.h"
#include "cheats.h"

extern Cheats* g_cheats;

SwapBuffersHook::tTargetPtr SwapBuffersHook::oFunction = nullptr;

BOOL WINAPI SwapBuffersHook::hookFunction(HDC hDc)
{
    // Initialize ImGui once on first call
    if (!GUI::initialized)
        GUI::initialize(hDc);

    // Run cheat logic every frame
    if (g_cheats)
        g_cheats->tick();

    // Draw GUI if visible
    if (GUI::initialized)
        GUI::draw();

    return SwapBuffersHook::oFunction(hDc);
}

SwapBuffersHook::SwapBuffersHook(void* openGl32Base)
{
    hookName   = "wglSwapBuffers";
    hookLen    = 14;
    moduleBase = openGl32Base;
    enabled    = false;
}

bool SwapBuffersHook::initialize()
{
    // GetProcAddress is reliable here — no sig scan needed for a known export
    targetAddr = GetProcAddress((HMODULE)moduleBase, "wglSwapBuffers");
    if (!targetAddr) {
        LOG("SwapBuffersHook: failed to find wglSwapBuffers");
        return false;
    }

    oFunction = (tTargetPtr)targetAddr;
    oFunction = (tTargetPtr)DetourFunction64(targetAddr, (void*)hookFunction, hookLen);
    enabled   = true;
    LOG("SwapBuffersHook: installed at %p", targetAddr);
    return true;
}
