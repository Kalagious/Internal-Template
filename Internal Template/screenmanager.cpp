#include "screenmanager.h"
#include "cheats.h"
#include <algorithm>


WNDPROC ScreenManager::hGameWindowProc;
bool ScreenManager::bShowGUI;

extern Cheats* cheatsGlobal;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowProc_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (ScreenManager::bShowGUI)
	{
		CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);
		return true;
	}

	// Otherwise call the game's wndProc function
	return CallWindowProc(ScreenManager::hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

ScreenManager::ScreenManager()
{
	hGameWindow = NULL;
	ScreenManager::bShowGUI = false;
	imGUIInitialized = false;
	bShowActiveModules = true;
}




BOOL CALLBACK ScreenManager::EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	int nameLen = GetWindowTextLength(hwnd);
	LPWSTR windowName = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(nameLen + 1), MEM_COMMIT, PAGE_READWRITE);
	if (windowName)
	{
		GetWindowText(hwnd, windowName, nameLen + 1);
		std::wstring wsName(windowName);

		uintptr_t windowProcessID = NULL;
		uintptr_t thread = GetWindowThreadProcessId(hwnd, (LPDWORD)&windowProcessID);
		if (windowProcessID == GetProcessId(GetCurrentProcess()) && wsName.find(L"Direct3D") != -1)
		{
			ScreenManager::gameWindowHandle = hwnd;
			return false;
		}
	}

	return true;
}


bool ScreenManager::GetGameWindow()
{
	EnumWindows(ScreenManager::EnumWindowsProc, NULL);
	if (ScreenManager::gameWindowHandle)
	{
		RecalculateWindowDimensions();
		return true;
	}
	return false;
}


bool ScreenManager::GetD3D9Device(void** table, size_t tableSize)
{
	if (!table)
		return false;

	IDirect3D11* d3d = Direct3DCreate11(D3D_SDK_VERSION);
	if (!d3d)
		return false;

	IDirect3DDevice9* d3dDeviceDummy = NULL;

	D3DPRESENT_PARAMETERS d3dParams = {};
	d3dParams.Windowed = false;
	d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParams.hDeviceWindow = ScreenManager::gameWindowHandle;

	HRESULT dummyCreated = d3d->CreateDevice(NULL, D3DDEVTYPE_HAL, d3dParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dParams, &d3dDeviceDummy);
	if (dummyCreated != S_OK)
	{
		d3dParams.Windowed = true;
		HRESULT dummyCreated = d3d->CreateDevice(NULL, D3DDEVTYPE_HAL, d3dParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dParams, &d3dDeviceDummy);
		if (dummyCreated != S_OK)
		{
			return false;
			d3d->Release();
		}

	}
	memcpy(table, *(void***)(d3dDeviceDummy), tableSize);
	d3dDeviceDummy->Release();
	d3d->Release();
	return true;
}









bool ScreenManager::initializeImGui(HDC hDc)
{
	hGameWindow = WindowFromDC(hDc);
	hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)windowProc_hook);
	if (!hGameWindow)
		return false;
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hGameWindow);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::CaptureMouseFromApp();

	ImGuiIO& io = ImGui::GetIO();
	char dllPath[512];

	GetCurrentDirectoryA(512, dllPath);

	std::string cwdStr(dllPath);

	cwdStr += "\\RobotoCondensed-Bold.ttf";
	printf("%s\n", cwdStr.c_str());

	pBodyFont = io.Fonts->AddFontFromFileTTF(cwdStr.c_str(), 24);
	pHeaderFont = io.Fonts->AddFontFromFileTTF(cwdStr.c_str(), 32);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_Header] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(0.1, 0.1, 0.1, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = ImVec4(0.2, 0.2, 0.2, 0.8);
	ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2, 0.2, 0.2, 0.8);



	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);
	ImGui::GetStyle().FrameBorderSize = 1;
	ImGui::GetStyle().WindowBorderSize = 2;
	ImGui::GetStyle().TabBorderSize = 1;
	ImGui::GetStyle().WindowRounding = 12;
	ImGui::GetStyle().FrameRounding = 4;






	imGUIInitialized = true;

	return true;
}

void ScreenManager::cleanUp()
{
	if (imGUIInitialized)
	{
		(WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)hGameWindowProc);

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}
	imGUIInitialized = false;
}