#pragma once

#include <Windows.h>
#include <RestartManager.h>
#pragma comment(lib, "Rstrtmgr.lib")

bool IsFileLocked(const wchar_t* PathName) {
    bool isFileLocked = false;

    DWORD dwSession = 0x0;
    wchar_t szSessionKey[CCH_RM_SESSION_KEY + 1] = { 0 };
    if (RmStartSession(&dwSession, 0x0, szSessionKey) == ERROR_SUCCESS) {
        if (RmRegisterResources(dwSession, 1, &PathName,
            0, NULL, 0, NULL) == ERROR_SUCCESS) {
            DWORD dwReason = 0x0;
            UINT nProcInfoNeeded = 0;
            UINT nProcInfo = 0;
            if (RmGetList(dwSession, &nProcInfoNeeded,
                &nProcInfo, NULL, &dwReason) == ERROR_MORE_DATA) {
                isFileLocked = (nProcInfoNeeded != 0);
            }
        }
        RmEndSession(dwSession);
    }

    return isFileLocked;
}
