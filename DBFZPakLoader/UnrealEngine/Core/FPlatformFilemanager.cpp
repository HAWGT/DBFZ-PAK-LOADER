#include "FPlatformFilemanager.h"
#include "../PakFile/IPlatformFilePak.h"
#include "../../Utils/GameHelper.h"

#include <Windows.h>

/*
* Reverse Info
* bool UMobileInstalledContent::Mount(int32 InPakOrder, const FString& InMountPoint)
* FPakPlatformFile* PakFileMgr = (FPakPlatformFile*)(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
* UE_LOG(LogMobilePatchingUtils, Log, TEXT("Mounted = %s, Order = %d, MountPoint = %s"), *PakFullName, PakOrder, !MountPount ? TEXT("(null)") : MountPount);
*/

FPlatformFilemanager* FPlatformFilemanager::getInstance()
{
	platformFilemanagerGetFunction = (std::uintptr_t)GameHelper::getInstance()->PatternScan(GameHelper::process_module, "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D ?? ?? ?? ?? BA 18 00 00 00 48 8B 0C C8 8B 04 0A 39 05 ?? ?? ?? ?? 7F 0C 48 8B 05 ?? ?? ?? ?? 48 83 C4 28 C3 48 8D 0D");
	if (platformFilemanagerGetFunction == (std::uintptr_t)nullptr) throw 0;
	static FPlatformFilemanager* instance = reinterpret_cast<FPlatformFilemanager*(__fastcall*)()>(platformFilemanagerGetFunction)(); //Find Saved & Config in ConfigManifest.cpp
	return instance;
}

IPlatformFilePak* FPlatformFilemanager::FindPlatformFile()
{
	findplatformFileFunction = (std::uintptr_t)GameHelper::getInstance()->PatternScan(GameHelper::process_module, "48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 20 48 8B 31 4C 8B F2 48 85 F6 74 60 0F 1F 00");
	//Can't be static because the value will change upon initialization
	if (findplatformFileFunction == (std::uintptr_t)nullptr) throw 0;
	IPlatformFilePak* instance = reinterpret_cast<IPlatformFilePak*(__fastcall*)(void*, __int64)>(findplatformFileFunction)(this, (__int64)L"PakFile"); //Searched for this string, few entries
	return instance;
}
