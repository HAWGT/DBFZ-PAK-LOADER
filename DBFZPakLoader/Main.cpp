#include <windows.h>

#include "UnrealEngine/UnrealStart.h"
#include <cstdio>


DWORD WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		UnrealStart::getInstance()->Intialize(hinstDLL);
		break;
	case DLL_PROCESS_DETACH:

		break;
	}

	return TRUE;
}
