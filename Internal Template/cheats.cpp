#include "cheats.h"
// #include "gui.h"  // uncomment when OpenGL hook is enabled

Cheats::Cheats()
{
    uninject = false;

    // Construct features
    exampleFeature = new ExampleFeature();

    

	// Find any needed pointers here, e.g.: players, viewatrix, weapons


    LOG("Cheats: constructed");
}

void Cheats::cheatUpdate()
{
    keybinds();

    // Tick each feature if enabled
    if (exampleFeature->enable) exampleFeature->tick();
    // Add more here as you create features:
    // if (myFeature->enable) myFeature->tick();
}

void Cheats::keybinds()
{
    // GUI::visible toggle goes here once OpenGL hook is enabled:
    // if (GetAsyncKeyState(VK_NUMPAD0) & 0x01)
    //     GUI::visible = !GUI::visible;

    // Toggle ExampleFeature with Numpad1
    if (GetAsyncKeyState(VK_NUMPAD1) & 0x01)
    {
        exampleFeature->enable = !exampleFeature->enable;
        LOG("ExampleFeature: %s", exampleFeature->enable ? "enabled" : "disabled");
    }

    // END: unload cheat
    if (GetAsyncKeyState(VK_END) & 0x01)
        uninject = true;
}

void Cheats::cleanup()
{
    delete exampleFeature;
    // delete myFeature;

    // GUI::shutdown();  // uncomment when OpenGL hook is enabled

    LOG("Cheats: cleaned up");
}
