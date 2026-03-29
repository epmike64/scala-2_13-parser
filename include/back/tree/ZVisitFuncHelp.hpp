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
		static void visitRegFunc(sp<fRegFunc> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunSig(sp<fFunSig> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitThisFunc(sp<fThisFunc> n, ssc prnSc, sp<fAstNodVisitor> visitor);
	};
}