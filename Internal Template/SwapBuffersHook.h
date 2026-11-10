#pragma once
#include "hooks.h"

// Hooks wglSwapBuffers (opengl32.dll) — fires every frame.
// This is where ImGui renders and feature ticks happen.
class SwapBuffersHook : public Hook {
public:
    SwapBuffersHook(void* openGl32Base);
    bool initialize();

    typedef BOOL(WINAPI* tTargetPtr)(HDC hDc);
    static tTargetPtr oFunction;
    static BOOL WINAPI hookFunction(HDC hDc);
};
