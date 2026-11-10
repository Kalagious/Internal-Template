#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <psapi.h>
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")

#pragma warning(disable: 26495)

void mainCode(HMODULE hModule);

// File-based debug log — console should also be open via AllocConsole in dllmain
#define LOG(fmt, ...) do { \
    printf("[CHEAT] " fmt "\n", ##__VA_ARGS__); \
    FILE* _f = fopen("C:\\cheat_debug.log", "a"); \
    if (_f) { fprintf(_f, "[CHEAT] " fmt "\n", ##__VA_ARGS__); fclose(_f); } \
} while(0)

class Vector2 {
public:
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    float x, y;
};

class Vector3 {
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    float x, y, z;
    float length() { return sqrtf(x*x + y*y + z*z); }
};

class Vector4 {
public:
    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    float x, y, z, w;
};

class Matrix4x4 {
public:
    float m[4][4];
    Matrix4x4() { memset(m, 0, sizeof(m)); }
};

#pragma warning(default: 26495)
