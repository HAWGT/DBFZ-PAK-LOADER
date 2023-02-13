#pragma once

#include <windows.h>

class UnrealStart {
public:
    static UnrealStart* getInstance() {
        static UnrealStart instance;
        return &instance;
    }

    void Intialize(HMODULE module);

private:
    UnrealStart() { }
};