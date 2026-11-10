#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <filesystem>

// ---------------------------------------------------------
// CONFIG — edit these two lines for your target
// ---------------------------------------------------------
static const wchar_t* TARGET_PROCESS = L"ac_client.exe";      // target process name
static const char*    DLL_NAME       = "Internal Template.dll"; // DLL filename (same dir as injector)
// ---------------------------------------------------------

DWORD GetProcessId(const wchar_t* procName)
{
    DWORD pid = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32W entry{ .dwSize = sizeof(entry) };
    if (Process32FirstW(snap, &entry))
    {
        do {
            if (_wcsicmp(entry.szExeFile, procName) == 0)
            {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snap, &entry));
    }
    CloseHandle(snap);
    return pid;
}

// Returns the full path to DLL_NAME sitting next to this injector exe
std::string GetDllPath()
{
    char injectorPath[MAX_PATH]{};
    GetModuleFileNameA(nullptr, injectorPath, MAX_PATH);

    std::filesystem::path p(injectorPath);
    p = p.parent_path() / DLL_NAME;
    return p.string();
}

int main()
{
    std::string dllPath = GetDllPath();

    printf("[*] DLL path : %s\n", dllPath.c_str());
    printf("[*] Target   : %ls\n", TARGET_PROCESS);

    // Verify the DLL actually exists before scanning
    if (GetFileAttributesA(dllPath.c_str()) == INVALID_FILE_ATTRIBUTES)
    {
        printf("[!] DLL not found at path above. Place it next to the injector.\n");
        system("pause");
        return 1;
    }

    printf("[*] Waiting for process...\n");
    DWORD pid = 0;
    while (!pid)
    {
        pid = GetProcessId(TARGET_PROCESS);
        Sleep(100);
    }
    printf("[*] Found PID %lu\n", pid);

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc || hProc == INVALID_HANDLE_VALUE)
    {
        printf("[!] OpenProcess failed (%lu). Run as admin.\n", GetLastError());
        system("pause");
        return 1;
    }

    // Write the DLL path string into the target process
    SIZE_T pathLen = dllPath.size() + 1;
    void* remoteMem = VirtualAllocEx(hProc, nullptr, pathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteMem)
    {
        printf("[!] VirtualAllocEx failed (%lu)\n", GetLastError());
        CloseHandle(hProc);
        system("pause");
        return 1;
    }

    WriteProcessMemory(hProc, remoteMem, dllPath.c_str(), pathLen, nullptr);

    // Inject
    HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0,
        (LPTHREAD_START_ROUTINE)LoadLibraryA, remoteMem, 0, nullptr);

    if (hThread)
    {
        WaitForSingleObject(hThread, 5000);
        CloseHandle(hThread);
        printf("[*] Injected successfully!\n");
    }
    else
    {
        printf("[!] CreateRemoteThread failed (%lu)\n", GetLastError());
    }

    VirtualFreeEx(hProc, remoteMem, 0, MEM_RELEASE);
    CloseHandle(hProc);

    system("pause");
    return 0;
}
