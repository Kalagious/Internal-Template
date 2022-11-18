#include "windows.h"
#include "cheats.h"
#include "general.h"
#include <tlhelp32.h>
#include <iostream>
#include "hookmanager.h"

Cheats* cheatsGlobal;

void mainCode(HMODULE hModule)
{

	//Cheats cheats;
	//cheatsGlobal = &cheats;

	//
	//while (!cheats.uninject)
	//{
	//	cheats.tick();
	//	if (GetAsyncKeyState(VK_END) & 0x01)
	//		cheats.uninject = true;
	//}
	//cheats.cleanup();

	FreeLibraryAndExitThread(hModule, 0);
}


