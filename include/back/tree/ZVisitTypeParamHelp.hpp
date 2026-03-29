#pragma once

#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/symbol/ZSymbol.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitTypeParamHelp {
	public:
		static void visitTypeParamClause(sp<fTypeParamClause> n, sbx prnSc, sp<fAstNodVisitor> visitor);
		static void visitVariantTypeParam(sp<fVariantTypeParam> n,  sbx prnSc, sp<fAstNodVisitor> visitor);

		static void buildVariantTypeParamClause(sp<fTypeParamClause> typeParamClause, sp<ZVariantTypeParamList> n, sbx prnSc,
		                                 sp<fAstNodVisitor> visitor);

		static void visitTypeParam(sp<fTypeParam> n,  sbx prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunTypeParamClause(sp<fFunTypeParamClause> n, sbx prnSc, sp<fAstNodVisitor> visitor);
	};

}
