#include "ExampleFeature.h"

ExampleFeature::ExampleFeature()
{
    name       = "ExampleFeature";
    enable     = false;
    m_tickCount = 0;
}

void ExampleFeature::tick()
{
    // This runs every iteration of the main loop while enable == true.
    // Replace this with your actual cheat logic.
    m_tickCount++;
    if (m_tickCount % 100 == 0)
        LOG("ExampleFeature: tick %d", m_tickCount);
}
