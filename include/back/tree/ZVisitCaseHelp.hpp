#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitCaseHelp {
		public:
		static void visitCaseClause(sp<fCaseClause> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitCaseClauses(sp<fCaseClauses> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitIf(sp<fIf> n, ssc prnSc, sp<fAstNodVisitor> visitor);

	};
}