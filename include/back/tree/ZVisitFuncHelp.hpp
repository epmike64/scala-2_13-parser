#pragma once



#include "ast/fLangOperand.hpp"
#include "ast/symbol/ZSymScope.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitFuncHelp {
	public:
		static void visitRegFunc(sp<fRegFunc> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunSig(sp<fFunSig> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitThisFunc(sp<fThisFunc> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};
}