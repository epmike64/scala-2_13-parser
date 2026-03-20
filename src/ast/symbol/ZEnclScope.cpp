#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope, sp<ZSymbol> zUnit)
		: parentScope_(std::move(parentScope)), zSymbol(std::move(zUnit)) {
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
}
