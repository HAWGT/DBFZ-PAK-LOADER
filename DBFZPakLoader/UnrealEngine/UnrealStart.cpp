#pragma once

#include "UnrealStart.h"

#include "../UnrealEngine/PakFile/IPlatformFilePak.h"
#include "../UnrealEngine/Core/FPlatformFilemanager.h"

#include "../Utils/FileChecker.h"

#include <cstdio>
#include <iostream>
#include <filesystem>
#include <thread>

HMODULE instance;

#ifdef _DEBUG
FILE* consoleIO;
#endif

void MountAllMods()
{
    FPlatformFilemanager* platform_file_manager;
    IPlatformFilePak* platform_file_pak;

    try {
        platform_file_manager = FPlatformFilemanager::getInstance();
    }
    catch(...)
    {
#ifdef _DEBUG
        std::cout << "[!] FPlatformFileManager::Get couldn't be found! Aborting..." << std::endl;
        return;
#else
        MessageBoxA(nullptr, "Error!", "DBFZ Pak Loader", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(instance, 0);
#endif
    }
#ifdef _DEBUG
        std::cout << "[+] FPlatformFilemanager: " << platform_file_manager << std::endl;
#endif

    try {
        platform_file_pak = IPlatformFilePak::getInstance();
    }
    catch (...)
    {
#ifdef _DEBUG
        std::cout << "[!] FPlatformFileManager::FindPlatformFile couldn't be found! Aborting..." << std::endl;
        return;
#else
        MessageBoxA(nullptr, "Error!", "DBFZ Pak Loader", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(instance, 0);
#endif
    }

#ifdef _DEBUG
    if (platform_file_pak == nullptr)
    {
        std::cout << "[?] Waiting for IPlatformFilePak..." << std::endl;
#endif
        while (platform_file_pak == nullptr)
        {
            platform_file_pak = IPlatformFilePak::getInstance();
        }
#ifdef _DEBUG
    }

    std::cout << "[+] IPlatformFilePak: " << platform_file_pak << std::endl;
#endif

    std::string target_extension = ".dbfz";

    const std::filesystem::path PaksPath = L"../../Content/Paks/";

    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(PaksPath))
    {
        if (entry.path().extension() != target_extension) continue;

        if (IsFileLocked(entry.path().c_str()))
        {
#ifdef _DEBUG
            std::cout << "[-] " << entry.path() << " is in use or has already been mounted." << std::endl;
#endif
            continue;
        }
        FString pak_file = entry.path().c_str();

        try
        {
#ifdef _DEBUG
            bool mounted = platform_file_pak->HandleMountPakDelegate(pak_file, 4);
            if (mounted)
            {
                std::cout << "[+] Mounted: " << pak_file.ToString() << std::endl;
            }
            else
            {
                std::cout << "[-] Failed to mount: " << pak_file.ToString() << std::endl;
            }
#else
            platform_file_pak->HandleMountPakDelegate(pak_file, 4);
#endif
        }
        catch (...)
        {
#ifdef _DEBUG
            std::cout << "[!] FPlatformFilePak::HandleMountPakDelegate couldn't be found! Aborting..." << std::endl;
            return;
#else
            MessageBoxA(nullptr, "Error!", "DBFZ Pak Loader", MB_OK | MB_ICONERROR);
            FreeLibraryAndExitThread(instance, 0);
#endif
        }
    }
#ifndef _DEBUG
    Beep(523, 500);
    Beep(587, 500);
    Beep(659, 500);
    Beep(698, 500);
    Beep(784, 500);
    FreeLibraryAndExitThread(instance, 0);
#endif
}

void UnrealStart::Intialize(HMODULE module)
{
    instance = module;

#ifdef _DEBUG
    auto CreateConsole = [](const char* name) {
        if (!AllocConsole())
            return;

        freopen_s(&consoleIO, "CONIN$", "r", stdin);
        freopen_s(&consoleIO, "CONOUT$", "w", stderr);
        freopen_s(&consoleIO, "CONOUT$", "w", stdout);

        SetConsoleTitleA(name);
    };


    CreateConsole("DBFZ Pak Loader");

    std::cout << "[+] DBFZ Pak Loader" << std::endl;
#endif

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MountAllMods, module, 0, nullptr);
}