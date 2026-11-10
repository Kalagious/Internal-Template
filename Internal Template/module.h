#pragma once
#include <string>

#pragma warning(disable: 26495)

// Base class for all cheat features.
// 1. Create a new file in features/ and inherit from Module
// 2. Implement tick() with your cheat logic
// 3. Add a pointer in cheats.h, construct it in Cheats(), add to cheatUpdate()
class Module {
public:
    bool        enable;
    std::string name;

    virtual void tick() {}
};

#pragma warning(default: 26495)
