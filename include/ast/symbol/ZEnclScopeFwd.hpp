#pragma once

#include <memory>

namespace zebra::ast::symbol{

	// Forward declaration only — avoids circular includes.
	// Full definition is in EnclosingScope.hpp.

	class ZSymbol;
	class ZTypeParam;
	class ZTraitDef;
	class ZClassDef;
	class ZSymScope;
	using esc = std::shared_ptr<ZSymScope>;

}

