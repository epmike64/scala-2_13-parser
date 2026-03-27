#include "util/fCommon.hpp"

namespace zebra::util {

	template<typename T, typename U>
	sp<T> dynSp(sp<U> basePtr) {
		sp<T> res = std::dynamic_pointer_cast<T>(basePtr);
		if (!res) {
			throw std::runtime_error("Failed to cast pointer of type " + std::string(typeid(U).name()) +
											 " to type " + std::string(typeid(T).name()));
		}
		return res;
	}

}