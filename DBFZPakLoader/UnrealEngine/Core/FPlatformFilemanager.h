#pragma once

#include <cstdint>

class IPlatformFilePak;
class FPlatformFilemanager {
private:
    inline static std::uintptr_t findplatformFileFunction;

    inline static std::uintptr_t platformFilemanagerGetFunction;
public:
    static FPlatformFilemanager* getInstance();

    IPlatformFilePak* FindPlatformFile();
};