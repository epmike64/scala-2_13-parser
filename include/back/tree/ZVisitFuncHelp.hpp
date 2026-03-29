#pragma once



#include "ast/fLangOperand.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitFuncHelp {
	public:
		static void visitRegFunc(sp<fRegFunc> n, sbx prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunSig(sp<fFunSig> n, sbx prnSc, sp<fAstNodVisitor> visitor);
		static void visitThisFunc(sp<fThisFunc> n, sbx prnSc, sp<fAstNodVisitor> visitor);
	};
}