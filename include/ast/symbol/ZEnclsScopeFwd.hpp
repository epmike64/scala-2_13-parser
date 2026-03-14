#pragma once

#include <memory>

namespace zebra::ast::symbol{

	// Forward declaration only — avoids circular includes.
	// Full definition is in EnclosingScope.hpp.
	class ZEnclosingScope;
	using esc = std::shared_ptr<ZEnclosingScope>;

}

