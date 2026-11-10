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

    // Feature instances — add one per feature
    ExampleFeature* exampleFeature;
};
