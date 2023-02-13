#pragma once

#include <cstdint>

inline std::uintptr_t GetAddressFromInstruction(std::uintptr_t address, int instruction_size)
{
	if (address == (std::uintptr_t)nullptr || instruction_size < 5) throw 0;
	return address + instruction_size + *(int*)(address + instruction_size - 4);
}
