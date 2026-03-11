#pragma once

#include <cstring>

namespace zebra::lex::util {

	constexpr char SP    = 0x20;
	constexpr char TAB   = 0x9;
	constexpr char LF    = 0xA;
	constexpr char FF    = 0xC;
	constexpr char CR    = 0xD;
	constexpr char EOI   = 0x1A;

	char* ensureCapacity(char* arr, const size_t currentSize, const size_t requiredSize);
}