#include "util/fUtil.hpp"

namespace zebra::util {

	void zaccert(bool condition, const std::string& message) {
		if (!condition) {
			throw std::runtime_error(message);
		}
	}

}