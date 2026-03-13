#include "ast/node/EnclosingScope.hpp"

namespace zebra::ast::node {

	EnclosingScope::EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd)
	: parentScope_(std::move(parentScope)), parentScopeGrmrProd_(parentScopeGrmrProd) {}

	fLangGrmrProdE EnclosingScope::getParentScopeGrmrProd() const {
		return parentScopeGrmrProd_;
	}

	esc EnclosingScope::getParentScope() const {
		return parentScope_;
	}

	void EnclosingScope::setPolishCalcStack(sp<std::stack<sp<fAstNod>>>&& astRPN) {
		this->polishCalcSS = std::move(astRPN);
	}

	sp<std::stack<sp<fAstNod>>> EnclosingScope::getPolishCalcStack() const {
		return polishCalcSS;
	}
}