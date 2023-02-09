#include "UnrealStart.h"

#include "../UnrealEngine/PakFile/IPlatformFilePak.h"
#include "../UnrealEngine/Core/FPlatformFilemanager.h"

#include <cstdio>
#include <iostream>
#include <filesystem>
#include <thread>

HMODULE instance;
//std::vector<FString> mountedPaks;

void MountAllMods()
{
#ifdef DEBUG
    std::cout << "FPlatformFilemanager: " << FPlatformFilemanager::getInstance() << std::endl;
#endif

    IPlatformFilePak* platform_file_pak = IPlatformFilePak::getInstance();

#ifdef DEBUG
    if (platform_file_pak == nullptr)
    {
        std::cout << "Waiting for IPlatformFilePak..." << std::endl;
#endif
        while (platform_file_pak == nullptr)
        {
            platform_file_pak = IPlatformFilePak::getInstance();
        }
#ifdef DEBUG
    }

    std::cout << "IPlatformFilePak: " << platform_file_pak << std::endl;
#endif

    std::string target_extension = ".pxk";

    const std::filesystem::path PaksPath = L"../../Content/Paks/";

    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(PaksPath))
    {
        if (entry.path().extension() != target_extension) continue;
        FString pak_file = entry.path().c_str();
#ifdef DEBUG
        bool mounted = IPlatformFilePak::getInstance()->HandleMountPakDelegate(pak_file, 4);
        if (mounted)
        {
            std::cout << "Mounted: " << pak_file.ToString() << std::endl;
            //mountedPaks.push_back(pak_file);
        }
        else 
        {
            std::cout << "Failed to mount: " << pak_file.ToString() << std::endl;
        }
#else
    IPlatformFilePak::getInstance()->HandleMountPakDelegate(pak_file, 4);
#endif
    }
    FreeLibraryAndExitThread(instance, 0);
}

/*void UnmountAllMods()
{
    for (const FString& pak_file : mountedPaks)
    {
        bool unMounted = IPlatformFilePak::getInstance()->HandleUnmountPakDelegate(pak_file);
        if (unMounted)
        {
            std::cout << "Unmounted: " << pak_file.ToString() << std::endl;
            mountedPaks.erase(mountedPaks.begin());
        }
        else
        {
            std::cout << "Failed to unmount: " << pak_file.ToString() << std::endl;
        }
    }
}*/

void UnrealStart::Intialize(HMODULE module)
{
    instance = module;

#ifdef DEBUG
    auto CreateConsole = [](const char* name) {
        if (!AllocConsole())
            return;

        FILE* fDummy;
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONOUT$", "w", stdout);

        SetConsoleTitleA(name);
    };


    CreateConsole("Debug Console");
#endif
    

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MountAllMods, module, 0, nullptr);
}