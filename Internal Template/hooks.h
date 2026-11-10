#pragma once
#include "general.h"

#pragma warning(disable: 26495)

// Generic hook base. Each specific hook extends this, calls DetourFunction64
// in its initialize(), and calls remove() on cleanup.
class Hook {
public:
    std::string hookName;
    uint32_t    hookLen;
    void*       moduleBase;
    void*       targetAddr;
    void*       trampAddr;
    uint8_t     stolenBytes[30];
    bool        enabled;
    std::vector<uint8_t> viSig;
    int32_t     iSigOffset;

    // Installs an abs64 jmp detour. Returns trampoline (call this to reach original).
    void* DetourFunction64(void* pSource, void* pDestination, int dwLen);

    // Sig scan within a loaded module. '?' in sig = 0x3F wildcard.
    void* signatureScan(std::vector<uint8_t> sig, int32_t offset, void* moduleBase);

    bool remove();
};

#pragma warning(default: 26495)
