#pragma once
#include "ast/node/fAstNodVisitor.hpp"


namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitStmtHelp {
		public:
		static void visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};


}
