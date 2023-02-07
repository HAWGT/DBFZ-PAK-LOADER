#include "IPlatformFilePak.h"
#include "../Core/FPlatformFilemanager.h"
#include "../../Utils/GameHelper.h"

IPlatformFilePak* IPlatformFilePak::getInstance()
{
    static IPlatformFilePak* platformInstance = FPlatformFilemanager::getInstance()->FindPlatformFile();
    return platformInstance;
}

bool IPlatformFilePak::MountPak(const TCHAR* InPakFilename, uint32 PakOrder, const TCHAR* InPath)
{
    static std::uintptr_t mountPakFunction = GameHelper::getInstance()->getBaseAddress() + 0x24E1740;
    bool isMounted = reinterpret_cast<void*(__fastcall*)(void*, const TCHAR*, uint32, const TCHAR*)>(mountPakFunction)(this, InPakFilename, PakOrder, InPath);
    return isMounted;
}

void* IPlatformFilePak::HandleMountPakDelegate(const FString& PakFilePath, int32 PakOrder)
{
    static std::uintptr_t handleMountPakDelegateFunction = GameHelper::getInstance()->getBaseAddress() + 0x24DEF50;
    reinterpret_cast<bool(__fastcall*)(void*, const FString&, int32, void*)>(handleMountPakDelegateFunction)(this, PakFilePath, PakOrder, nullptr); //Seached for %sPaks/%s- from Initialize

    return 0;
}
