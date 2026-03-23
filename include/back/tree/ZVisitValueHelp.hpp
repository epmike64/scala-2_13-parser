#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitValueHelp {
		public:
		static void visitValDef(sp<fValueDef> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitValDecl(sp<fValueDecl> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};
}