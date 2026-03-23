#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitCaseHelp {
		public:
		static void visitCaseClause(sp<fCaseClause> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitCaseClauses(sp<fCaseClauses> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitIf(sp<fIf> n, esc prnSc, sp<fAstNodVisitor> visitor);

	};
}