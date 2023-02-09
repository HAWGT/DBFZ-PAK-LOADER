#include "FPlatformFilemanager.h"
#include "../PakFile/IPlatformFilePak.h"
#include "../../Utils/GameHelper.h"

#include <cstdint>

/*
* Reverse Info
* bool UMobileInstalledContent::Mount(int32 InPakOrder, const FString& InMountPoint)
* FPakPlatformFile* PakFileMgr = (FPakPlatformFile*)(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
* UE_LOG(LogMobilePatchingUtils, Log, TEXT("Mounted = %s, Order = %d, MountPoint = %s"), *PakFullName, PakOrder, !MountPount ? TEXT("(null)") : MountPount);
*/

FPlatformFilemanager* FPlatformFilemanager::getInstance()
{
	static std::uintptr_t platformFilemanagerInstance = GameHelper::getInstance()->getBaseAddress() + 0x936100;
	static FPlatformFilemanager* instance = reinterpret_cast<FPlatformFilemanager*(__fastcall*)()>(platformFilemanagerInstance)(); //Find Saved & Config in ConfigManifest.cpp
	return instance;
}

IPlatformFilePak* FPlatformFilemanager::FindPlatformFile()
{
	static std::uintptr_t findplatformFileFunction = GameHelper::getInstance()->getBaseAddress() + 0x934C00;
	//Can't be static because the value will change upon initialization
	IPlatformFilePak* instance = reinterpret_cast<IPlatformFilePak*(__fastcall*)(void*, __int64)>(findplatformFileFunction)(this, (__int64)L"PakFile"); //Searched for this string, few entries
	return instance;
}
