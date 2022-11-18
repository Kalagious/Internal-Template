#include "cheats.h"
#include "windows.h"


#define gModule(x) (void*)GetModuleHandle(x)


Cheats::Cheats()
{
	uninject = true;

	soTGameExe = gModule(L"SoTGame.exe");
	d3D11Dll = gModule(L"d3d11.dll");

	hookManager = new HookManager(soTGameExe, NULL);
	screenManager = new ScreenManager();

	fly = new Fly(this);

	uninject = false;
	addressesAreValid = false;
}

void Cheats::tick()
{
	keybinds();
	if (addressesAreValid)
	{
		//Blah
	}
	else
	{
		recalculateAddresses();
	}
}

void Cheats::recalculateAddresses()
{
	//hookManager->InitalizeHooks();
	addressesAreValid = true;
}

void Cheats::cleanup()
{
	//hookManager->removeAll();
	//screenManager->cleanUp();
	Sleep(200);
}