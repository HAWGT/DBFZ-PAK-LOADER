#pragma once

#include <cstdint>

inline std::uintptr_t GetAddressFromInstruction(std::uintptr_t address, int instruction_size)
{
	int offset = instruction_size - 4;
	return address + instruction_size + *(int*)(address + offset);
}
