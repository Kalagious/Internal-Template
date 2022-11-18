#include "hookmanager.h"

HookManager::HookManager(void* tlopoExeIn, void* openGl32In)
{
	tlopoExe = tlopoExeIn;
	openGl32 = openGl32In;


	pyObject_SetAttrHook = new PyObject_SetAttrHook(tlopoExe);
	swapBuffersHook = new SwapBuffersHook(openGl32);

	bHooksInitialized = false;
}


void HookManager::InitalizeHooks()
{
	printf(" [*] Initializing Game Hooks:\n");

	if (!pyObject_SetAttrHook->enabled)
		pyObject_SetAttrHook->initialize();
	if (!swapBuffersHook->enabled)
		swapBuffersHook->initialize();

	printf(" [*] Hooks Initialized!\n\n");
	bHooksInitialized = true;
}


void HookManager::removeAll()
{

	if (pyObject_SetAttrHook->enabled)
		pyObject_SetAttrHook->remove();
	if (swapBuffersHook->enabled)
		swapBuffersHook->remove();

	Sleep(10);
}
