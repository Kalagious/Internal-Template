#include "cheats.h"
// #include "gui.h"  // uncomment when OpenGL hook is enabled

Cheats::Cheats()
{
    uninject = false;

    // --- Module base addresses ---
    // GetModuleHandle returns the base address of a loaded module in this process.
    // Use this to calculate offsets: moduleBase + 0x1234 = absolute address.
    moduleBase = (uintptr_t)GetModuleHandleA("ac_client.exe");
    LOG("ac_client.exe base: %p", (void*)moduleBase);

    // --- Game pointers ---
    // localPlayer is stored as a static pointer at a fixed offset from the module base.
    // Dereferencing it gives the address of the actual player object.
    // Replace 0x10F4F4 with the real offset for your target (find it in Cheat Engine).
    uintptr_t localPlayerPtr = moduleBase + 0x10F4F4;
    localPlayer = *(uintptr_t*)localPlayerPtr;
    LOG("localPlayer: %p", (void*)localPlayer);

    // --- Construct features ---
    exampleFeature = new ExampleFeature();

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
