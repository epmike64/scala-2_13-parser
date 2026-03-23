#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;
	class ZVisitLoopHelp {
 	public:
 		static void visitWhileLoop(sp<fWhile> n, esc prnSc, sp<fAstNodVisitor> visitor);
 		static void visitForLoop(sp<fFor> n, esc prnSc, sp<fAstNodVisitor> visitor);
 	};
}