#pragma once

#include "ast/leaf/fClassParamClauses.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitTypeParamHelp {
	public:
		static void visitTypeParamClause(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitVariantTypeParam(sp<fVariantTypeParam> n,  esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTypeParam(sp<fTypeParam> n,  esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunTypeParamClause(sp<fFunTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};

}
