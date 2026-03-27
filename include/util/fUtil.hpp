#pragma once
#include <stdexcept>

namespace zebra::util {

	void zaccert(bool condition, const std::string& message);

}
