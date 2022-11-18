#include "PresentHook.h"
#include "screenmanager.h"
#include "cheats.h"

extern Cheats* cheatsGlobal;
extern ScreenManager* screenManagerGlobal;

PresentHook::tTargetPtr PresentHook::oFunction;

HRESULT __fastcall HookFunction(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags) {

	if (!ScreenManager::d3dDevice)
		ScreenManager::d3dDevice = device;

	if (!screenManagerGlobal->imGUIIsInitialized && ScreenManager::d3dDevice)
		screenManagerGlobal->InitializeImGUI();

	if (screenManagerGlobal->imGUIIsInitialized)
		screenManagerGlobal->DrawImGUI();

	return oFunction(pChain, SyncInterval, Flags)
}



PresentHook::PresentHook(uintptr_t endSceneAddr)
{
	hookName = "End Scene Hook";
	hookLen = 7;
	moduleBase = NULL;
	targetAddr = endSceneAddr;
	enabled = false;
	PresentHook::oFunction = (tTargetPtr)(targetAddr);
}


bool PresentHook::initialize()
{
	PresentHook::oFunction = (tTargetPtr)(targetAddr);
	PresentHook::oFunction = (tTargetPtr)DetourFunction64((void*)PresentHook::oFunction, (void*)PresentHook::hookFunction, hookLen);
	enabled = true;
	return true;
}