#include "hooks.h"

bool Hook::remove()
{
    LOG("Unhooking %s at %p", hookName.c_str(), targetAddr);
    DWORD oldProtect;
    VirtualProtect(targetAddr, hookLen, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(targetAddr, stolenBytes, hookLen);
    VirtualProtect(targetAddr, hookLen, oldProtect, &oldProtect);
    enabled = false;
    return true;
}

void* Hook::DetourFunction64(void* pSource, void* pDestination, int dwLen)
{
    const int MinLen = 14;
    if (dwLen < MinLen) return nullptr;

    // abs64 jmp stub: FF 25 00000000 <8-byte-addr>
    BYTE stub[] = {
        0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    void* pTrampoline = VirtualAlloc(nullptr, dwLen + sizeof(stub),
                                     MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!pTrampoline) return nullptr;

    DWORD dwOld = 0;
    VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);
    memcpy(stolenBytes, pSource, dwLen);

    // Build trampoline: stolen bytes + jmp back to pSource+dwLen
    DWORD64 retTo = (DWORD64)pSource + dwLen;
    memcpy(stub + 6, &retTo, 8);
    memcpy(pTrampoline, pSource, dwLen);
    memcpy((BYTE*)pTrampoline + dwLen, stub, sizeof(stub));

    // Patch source: jmp to destination
    memcpy(stub + 6, &pDestination, 8);
    memcpy(pSource, stub, sizeof(stub));

    // NOP any leftover bytes
    for (int i = MinLen; i < dwLen; i++)
        *(BYTE*)((uintptr_t)pSource + i) = 0x90;

    VirtualProtect(pSource, dwLen, dwOld, &dwOld);
    return pTrampoline;
}

void* Hook::signatureScan(std::vector<uint8_t> sig, int32_t offset, void* base)
{
    if (sig.empty()) { LOG("SigScan: empty sig"); return nullptr; }

    MODULEINFO mi{};
    GetModuleInformation(GetCurrentProcess(), (HMODULE)base, &mi, sizeof(mi));
    if (!mi.SizeOfImage) { LOG("SigScan: failed to get module info"); return nullptr; }

    int matches = 0;
    for (uint64_t i = 0; i < mi.SizeOfImage; i++)
    {
        uint8_t byte = *(uint8_t*)((uint64_t)base + i);
        if (byte == sig[matches] || sig[matches] == 0x3F)
            matches++;
        else
            matches = 0;

        if (matches >= (int)sig.size())
        {
            void* result = (void*)((uint64_t)base + i - sig.size() - offset + 1);
            LOG("SigScan [%s]: found at %p", hookName.c_str(), result);
            return result;
        }
    }

    LOG("SigScan [%s]: NOT found", hookName.c_str());
    return nullptr;
}
