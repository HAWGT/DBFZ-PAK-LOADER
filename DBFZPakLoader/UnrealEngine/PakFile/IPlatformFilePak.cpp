#include "IPlatformFilePak.h"
#include "../Core/FPlatformFilemanager.h"
#include "../../Utils/GameHelper.h"

IPlatformFilePak* IPlatformFilePak::getInstance()
{
    //Can't be static because the value will change upon initialization
    IPlatformFilePak* platformInstance = FPlatformFilemanager::getInstance()->FindPlatformFile();
    return platformInstance;
}

bool IPlatformFilePak::HandleMountPakDelegate(const FString& PakFilePath, int32 PakOrder)
{
    static std::uintptr_t handleMountPakDelegateFunction = GameHelper::getInstance()->getBaseAddress() + 0x24DEF50;
    bool mounted = reinterpret_cast<bool(__fastcall*)(void*, const FString&, int32, void*)>(handleMountPakDelegateFunction)(this, PakFilePath, PakOrder, nullptr); //Seached for %sPaks/%s- from Initialize
    return mounted;
}

bool IPlatformFilePak::HandleUnmountPakDelegate(const FString& PakFilePath)
{
    static std::uintptr_t handleUnmountPakDelegateFunction = GameHelper::getInstance()->getBaseAddress() + 0x24DF150;
    bool unMounted = reinterpret_cast<bool(__fastcall*)(void*, const FString&)>(handleUnmountPakDelegateFunction)(this, PakFilePath); //Right after
    return unMounted;
}
