#include "ast/symbol/ZSymScope.hpp"

namespace zebra::ast::symbol {
	ZSymScope::ZSymScope(esc parentScope)
		: parentScope_(parentScope) {
	}

	esc ZSymScope::getParentScope() const {
		return parentScope_;
	}

	sp<ZSymbol> ZSymScope::getZSymbol() {
		return zSymbol_;
	}

	void ZSymScope::setZSymbol(sp<ZSymbol> zSymbol) {
		this->zSymbol_ = zSymbol;
	}
}
