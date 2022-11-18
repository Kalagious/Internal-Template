#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <tlHelp32.h>
#include <stdint.h>
#include <tchar.h>

#include "PyObject_SetAttrHook.h"
#include "SwapBuffersHook.h"

class HookManager
{
public:

	HookManager(void* tlopoExeIn, void* openGl32In);
	void removeAll();
	void InitalizeHooks();
	bool bHooksInitialized;

	PyObject_SetAttrHook* pyObject_SetAttrHook;
	SwapBuffersHook* swapBuffersHook;
	void* tlopoExe;
	void* openGl32;

};