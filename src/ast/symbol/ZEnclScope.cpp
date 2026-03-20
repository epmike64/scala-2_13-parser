#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope, sp<ZUnit> zUnit)
		: parentScope_(std::move(parentScope)), zUnit(std::move(zUnit)) {
	}

	ZLangConstruct ZEnclScope::getLangConstruct() const {
		return zUnit->getZLangConstruct();
	}

	esc ZEnclScope::getParentScope() const {
		return parentScope_;
	}



	sp<ZUnit> ZEnclScope::getZUnit() {
		return zUnit;
	}
}
