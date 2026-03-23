#pragma once

#include "ast/leaf/fClassParamClauses.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitTypeParamHelp {
	public:
		// static void visitClassParamClauses(sp<fClassParamClauses> n, esc prnSc, sp<fAstNodVisitor> visitor);
		// static void visitClassParam(sp<fClassParam> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTypeParamClauses(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitVariantTypeParam(sp<fVariantTypeParam> n,  esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTypeParam(sp<fTypeParam> n,  esc prnSc, sp<fAstNodVisitor> visitor);
		// static void visitParam(sp<fParam> par, esc prnSc, sp<fAstNodVisitor> visitor);
		// static void visitParamTypes(sp<fParamTypes> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};

}
