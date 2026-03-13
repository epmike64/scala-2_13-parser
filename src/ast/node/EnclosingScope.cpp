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

	void EnclosingScope::setLbrSS(sp<std::stack<sp<fLangTrBranch>>>&& lbrSS) {
		this->lbrSS_ = std::move(lbrSS);
	}

	sp<std::stack<sp<fLangTrBranch>>> EnclosingScope::getLbrSS() const {
		return lbrSS_;
	}

}