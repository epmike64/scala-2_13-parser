#pragma once

#include <memory>

namespace zebra::ast::node {

	// Forward declaration only — avoids circular includes.
	// Full definition is in EnclosingScope.hpp.
	class EnclosingScope;
	using esc = std::shared_ptr<EnclosingScope>;

}

