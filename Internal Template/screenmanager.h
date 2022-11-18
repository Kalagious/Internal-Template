#pragma once
#include "general.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"
#include <string>

class ScreenManager
{
public:

	ScreenManager();

	bool imGUIInitialized;
	bool bShowActiveModules;
	bool dDoRGB;
	static bool bShowGUI;

	bool initializeImGui(HDC hDc);
	void cleanUp();

	bool GetGameWindow();
	bool GetD3D9Device(void** table, size_t tableSize);


	static LPDIRECT3DDEVICE9 d3dDevice;
	EndSceneHook* endSceneHook;
	static HWND gameWindowHandle;
	typedef LRESULT(CALLBACK* OrigWndProcT)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static OrigWndProcT origWndProc;


	void drawGUI();


	void DrawMovementCategory();
	void DrawGeneralCategory();
	void DrawVisualCategory();
	void DrawAttackCategory();
	void DrawActive();
	void DrawMain();
	void DrawHelp();


	ImFont* pBodyFont;
	ImFont* pHeaderFont;
	HWND hGameWindow;
	static WNDPROC hGameWindowProc;
};

