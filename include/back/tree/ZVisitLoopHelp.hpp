#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;
	class ZVisitLoopHelp {
	public:
		static void visitWhileLoop(sp<fWhile> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitForLoop(sp<fFor> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitGenerator(sp<fGenerator> n, ssc prnSc, sp<fAstNodVisitor> visitor);
	};
}