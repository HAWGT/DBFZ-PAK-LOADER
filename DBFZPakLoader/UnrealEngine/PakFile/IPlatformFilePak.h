#pragma once

#include <tchar.h>
#include <string>
#include <locale>
#include <cstdint>

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

template <class T>
struct TArray {
	friend struct FString;
public:

	T* Data;
	int32_t Count;
	int32_t Max;

	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}
};

struct FString : private TArray<wchar_t> {
	inline FString() {};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? int32_t(std::wcslen(other)) + 1 : 0;
		if (Count)
			Data = const_cast<wchar_t*>(other);
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
		return str;
	}

	std::wstring ToWString() const
	{
		std::wstring str(Data);
		return str;
	}

};

class IPlatformFilePak {
private:
	inline static std::uintptr_t handleMountPakDelegateFunction;
	inline static std::uintptr_t fPakPrecacherShutdownFunction;
public:
    static IPlatformFilePak* getInstance();

    bool HandleMountPakDelegate(const FString& PakFilePath, int32 PakOrder);

	void KillSigChecker();
};
