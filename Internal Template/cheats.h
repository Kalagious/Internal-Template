#pragma once
#include "screenmanager.h"
#include "allmodules.h"
#include "module.h"
#include "allclasses.h"
#include "hookmanager.h"



class Cheats {
public:
	Cheats();
	void tick();
	void keybinds();
	void recalculateAddresses();
	void cleanup();

	bool uninject;
	bool addressesAreValid;

	void* soTGameExe;
	void* d3D11Dll;
	//void* openGl32;

	std::vector<Module*> modules;

	HookManager* hookManager;
	ScreenManager* screenManager;


	Fly* fly;
};