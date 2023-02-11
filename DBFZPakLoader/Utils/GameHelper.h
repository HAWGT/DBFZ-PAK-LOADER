#pragma once

#include <cstdint>
#include <Windows.h>

class GameHelper {
public:
    inline static const HMODULE process_module = GetModuleHandleA(nullptr);

    static GameHelper* getInstance() {
        static GameHelper instance;
        return &instance;
    }
    
    std::uintptr_t getBaseAddress();

    std::uint8_t* PatternScan(void* module, const char* signature);
};