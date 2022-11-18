#pragma once
#include "hooks.h"


class PresentHook : public Hook
{
public:

	bool initialize();
	PresentHook(uintptr_t endSceneAddr);
	typedef HRESULT(APIENTRY* tTargetPtr)(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags);
	static tTargetPtr oFunction;
	static void APIENTRY hookFunction(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags);
};

