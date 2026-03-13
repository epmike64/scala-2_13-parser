#include "ast/node/EnclosingScope.hpp"

namespace zebra::ast::node {

	void EnclosingScope::setParentScope(esc parentScope) {
		parentScope_ = parentScope;
	}
	esc EnclosingScope::getParentScope() {
		return parentScope_;
	}

	void EnclosingScope::setLbrSS(sp<std::stack<sp<fLangTrBranch>>>&& lbrSS) {
		this->lbrSS_ = std::move(lbrSS);
	}

	sp<std::stack<sp<fLangTrBranch>>> EnclosingScope::getLbrSS() const {
		return lbrSS_;
	}

}