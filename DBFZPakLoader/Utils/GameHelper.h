#pragma once
#include <cstdint>

class GameHelper {
public:
    static GameHelper* getInstance() {
        static GameHelper instance;
        return &instance;
    }
    
    std::uintptr_t getBaseAddress();

    std::uint8_t* PatternScan(void* module, const char* signature);

};