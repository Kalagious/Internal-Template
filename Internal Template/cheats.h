#pragma once
#include "general.h"
#include "module.h"
#include "features/ExampleFeature.h"
// Add more feature headers here as you create them

class Cheats {
public:
    Cheats();
    void cheatUpdate();  // called every loop tick — runs all modules
    void keybinds();
    void cleanup();

    bool uninject;

    // Module base addresses
    uintptr_t moduleBase;   // ac_client.exe

    // Game pointers — read from memory each tick or cache here
    uintptr_t localPlayer;  // pointer to local player object

    // Feature instances — add one per feature
    ExampleFeature* exampleFeature;
};
