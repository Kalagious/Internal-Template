#include "gui.h"
#include "cheats.h"

extern Cheats* g_cheats;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

bool    GUI::initialized  = false;
bool    GUI::visible      = false;   // GUI hidden by default — toggle with Numpad0
HWND    GUI::hwnd         = nullptr;
WNDPROC GUI::origWndProc  = nullptr;

LRESULT CALLBACK GUI::wndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (GUI::visible)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
        return true;
    }
    return CallWindowProc(GUI::origWndProc, hWnd, msg, wParam, lParam);
}

bool GUI::initialize(HDC hDc)
{
    hwnd = WindowFromDC(hDc);
    if (!hwnd) { LOG("GUI: WindowFromDC failed"); return false; }

    origWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wndProcHook);

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init();

    ImGuiStyle& s = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    s.WindowRounding    = 8.f;
    s.FrameRounding     = 4.f;
    s.WindowTitleAlign  = ImVec2(0.5f, 0.5f);
    s.WindowBorderSize  = 1.f;
    s.FrameBorderSize   = 1.f;

    initialized = true;
    LOG("GUI: initialized");
    return true;
}

void GUI::draw()
{
    if (!visible) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ---- Main menu window ----
    ImGui::SetNextWindowSize(ImVec2(350, 500), ImGuiCond_Once);
    ImGui::Begin("Cheat Menu");

    // General tab
    if (ImGui::CollapsingHeader("General"))
    {
        // Add general features here, e.g.:
        // ImGui::Checkbox("No Recoil", &g_cheats->noRecoil->enable);
        ImGui::Text("No features yet — add them here.");
    }

    ImGui::Separator();
    ImGui::Text("Numpad0 = toggle menu  |  END = unload");

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::shutdown()
{
    if (!initialized) return;
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)origWndProc);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    initialized = false;
    LOG("GUI: shut down");
}
