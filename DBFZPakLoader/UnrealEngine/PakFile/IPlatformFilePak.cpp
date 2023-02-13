#pragma once

#include "IPlatformFilePak.h"
#include "../Core/FPlatformFilemanager.h"
#include "../../Utils/GameHelper.h"
#include "../../Utils/AddressHelper.h"

#include <windows.h>

IPlatformFilePak* IPlatformFilePak::getInstance()
{
    //Can't be static because the value will change upon initialization
    IPlatformFilePak* platformInstance;
    try {
        platformInstance = FPlatformFilemanager::getInstance()->FindPlatformFile();
    }
    catch(...)
    {
        throw 0;
    }
    return platformInstance;
}

bool IPlatformFilePak::HandleMountPakDelegate(const FString& PakFilePath, int32 PakOrder)
{
    if (handleMountPakDelegateFunction == (std::uintptr_t)nullptr) handleMountPakDelegateFunction = (std::uintptr_t)GameHelper::getInstance()->PatternScan(GameHelper::process_module, "41 54 41 55 41 56 41 57 48 81 EC A8 00 00 00 83 7A 08 00 4D 8B E1 4C 8B F2 4C 8B F9 74 05 48 8B 12 EB 07 48 8D 15");
    if (handleMountPakDelegateFunction == (std::uintptr_t)nullptr) throw 0;
    bool mounted = reinterpret_cast<bool(__fastcall*)(void*, const FString&, int32, void*)>(handleMountPakDelegateFunction)(this, PakFilePath, PakOrder, nullptr); //Seached for %sPaks/%s- from Initialize
    return mounted;
}

void IPlatformFilePak::KillSigChecker()
{
    *(std::byte*)(this + 0x20) = (std::byte)0; //bSigned
    if (GPakCache_Enable == nullptr) GPakCache_Enable = (int*)GetAddressFromInstruction((std::uintptr_t)(GameHelper::getInstance()->PatternScan(GameHelper::process_module, "89 1D ?? ?? ?? ?? 48 8B 8C 24 D0 00 00 00 48 33 CC E8 ?? ?? ?? ?? 48 8B 9C 24 00 01 00 00 48 81 C4 E0 00 00 00 5E C3 CC CC CC CC CC")), 6);
    *GPakCache_Enable = 0; //GPakCache_Enable - Look for FileOpenLog
}

