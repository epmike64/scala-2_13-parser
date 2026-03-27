#pragma once
#include <stdexcept>

namespace zebra::util {

	void zaccert(bool condition, const std::string& message) {
		if (condition) {
			throw std::logic_error(message);
		}
	}

}
