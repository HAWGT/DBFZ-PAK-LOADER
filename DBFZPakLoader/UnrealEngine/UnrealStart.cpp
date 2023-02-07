#include "UnrealStart.h"

#include "../UnrealEngine/PakFile/IPlatformFilePak.h"
#include "../UnrealEngine/Core/FPlatformFilemanager.h"

#include <cstdio>
#include <iostream>
#include <filesystem>
#include <thread>

HMODULE instance;

void ModMounter()
{
    //printf("FPlatformFilemanager: 0x%llx\n", FPlatformFilemanager::getInstance());
    //printf("IPlatformFilePak: 0x%llx\n", IPlatformFilePak::getInstance());

    std::string target_extension = ".pxk";

    const std::filesystem::path PaksPath = L"../../Content/Paks/";

    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(PaksPath))
    {
        if (entry.path().extension() != target_extension) continue;
        FString pak_file = entry.path().c_str();
        void* Pak = IPlatformFilePak::getInstance()->HandleMountPakDelegate(pak_file, 4);
        //std::cout << pak_file.ToString() << std::endl;
    }

    FreeLibraryAndExitThread(instance, 0);
}

void UnrealStart::Intialize(HMODULE module)
{
    instance = module;

    /*
    auto CreateConsole = [](const char* name) {
        if (!AllocConsole())
            return;

        FILE* fDummy;
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONOUT$", "w", stdout);

        SetConsoleTitleA(name);
    };

    CreateConsole("DBFZ Mod Enabler");
    */
    

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ModMounter, module, 0, nullptr);
}