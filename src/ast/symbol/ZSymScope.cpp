#include "ast/symbol/ZSymScope.hpp"

namespace zebra::ast::symbol {
	ZSymScope::ZSymScope(ssc parentScope)
		: parentScope_(parentScope) {
	}

	ssc ZSymScope::getParentScope() const {
		return parentScope_;
	}

	sp<ZSymbol> ZSymScope::getZSymbol() {
		return zSymbol_;
	}

	void ZSymScope::setZSymbol(sp<ZSymbol> zSymbol) {
		this->zSymbol_ = zSymbol;
	}
}
