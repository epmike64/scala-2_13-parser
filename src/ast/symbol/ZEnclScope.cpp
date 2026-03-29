#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope)
		: parentScope_(parentScope) {
	}

	esc ZEnclScope::getParentScope() const {
		return parentScope_;
	}

	sp<ZSymbol> ZEnclScope::getZSymbol() {
		return zSymbol_;
	}

	void ZEnclScope::setZSymbol(sp<ZSymbol> zSymbol) {
		this->zSymbol_ = zSymbol;
	}
}
