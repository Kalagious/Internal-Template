#pragma once
#include "general.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui_impl_win32.h"

// All GUI state is static — one instance, lives for the lifetime of the cheat.
// Set GUI::visible = true (Numpad0) to show the menu.
class GUI {
public:
    static bool initialized;
    static bool visible;
    static HWND  hwnd;
    static WNDPROC origWndProc;

    static bool initialize(HDC hDc);
    static void draw();
    static void shutdown();

    // WndProc hook to capture mouse/kb input for ImGui when menu is open
    static LRESULT CALLBACK wndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
