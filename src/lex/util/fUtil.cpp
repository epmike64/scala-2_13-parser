#include "lex/util/fUtil.hpp"

#include <cassert>

namespace zebra::lex::util {

	char* ensureCapacity(char* arr, const size_t currentSize, const size_t requiredSize) {
		assert(currentSize >= 0 && requiredSize >= 0);
		if (currentSize >= requiredSize) {
			return arr;
		}

		size_t newSize = requiredSize * 2;
		char* newArr = new char[newSize];
		if (arr) {
			std::memcpy(newArr, arr, currentSize);
			delete [] arr;
		}
		return newArr;
	}

}