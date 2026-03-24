#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope, sp<ZSymbol> zSymbol)
		: parentScope_(std::move(parentScope)), zSymbol(std::move(zSymbol)) {
	}

	ZLangConstruct ZEnclScope::getLangConstruct() const {
		return zSymbol->getZLangConstruct();
	}

	esc ZEnclScope::getParentScope() const {
		return parentScope_;
	}

	sp<ZSymbol> ZEnclScope::getZSymbol() {
		return zSymbol;
	}

	void ZEnclScope::setZSymbol(sp<ZSymbol> zSymbol) {
		this->zSymbol = zSymbol;
	}
}
