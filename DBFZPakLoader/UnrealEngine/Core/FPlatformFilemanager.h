#pragma once

class IPlatformFilePak;
class FPlatformFilemanager {
public:
    static FPlatformFilemanager* getInstance();

    IPlatformFilePak* FindPlatformFile();
};