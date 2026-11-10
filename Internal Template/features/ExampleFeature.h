#pragma once
#include "../module.h"
#include "../general.h"

// Example feature — rename this file and class for your actual cheat.
// Steps to add your own:
//   1. Copy this file, rename the class
//   2. Add your logic in tick()
//   3. Include in cheats.h and wire up (see comments there)
class ExampleFeature : public Module {
public:
    ExampleFeature();
    void tick() override;

private:
    int m_tickCount;
};
