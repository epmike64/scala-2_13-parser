#pragma once

#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/symbol/ZSymbol.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitTypeParamHelp {
	public:
		static void visitTypeParamClause(sp<fTypeParamClause> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitVariantTypeParam(sp<fVariantTypeParam> n,  ssc prnSc, sp<fAstNodVisitor> visitor);

		static void buildVariantTypeParamClause(sp<fTypeParamClause> typeParamClause, sp<ZVariantTypeParamList> n, ssc prnSc,
		                                 sp<fAstNodVisitor> visitor);

		static void visitTypeParam(sp<fTypeParam> n,  ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunTypeParamClause(sp<fFunTypeParamClause> n, ssc prnSc, sp<fAstNodVisitor> visitor);
	};

}
