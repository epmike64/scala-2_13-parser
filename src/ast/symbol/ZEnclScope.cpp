#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope, ZLangConstruct lc)
		: parentScope_(std::move(parentScope)), scopeLangConstruct(lc) {
	}

	ZLangConstruct ZEnclScope::getLangConstruct() const {
		return scopeLangConstruct;
	}

	esc ZEnclScope::getParentScope() const {
		return parentScope_;
	}

	void ZEnclScope::setPolishSS(sp<std::vector<sp<fAstNod> > > &&astRPN) {
		this->polishCalcStack = std::move(astRPN);
	}

	sp<std::vector<sp<fAstNod> > > ZEnclScope::getPolishSS() const {
		return polishCalcStack;
	}

	void ZEnclScope::addZUnit(sp<ZUnit> zu) {
		if (zunitMap_ == nullptr) {
			zunitMap_ = ms<std::unordered_map<ZId, sp<ZUnit>>>();
		}
		auto it = zunitMap_->find(zu->zId());
		if (it != zunitMap_->end()) {
			throw std::runtime_error("Symbol with ID " + zu->zId().qualId() + " already exists in the current scope");
		}
		(*zunitMap_)[zu->zId()] = zu;
	}

	sp<ZUnit> ZEnclScope::getZUnit(const ZId zid) {
		if (zunitMap_ == nullptr) {
			return nullptr;
		}
		auto it = zunitMap_->find(zid);
		if (it != zunitMap_->end()) {
			return it->second;
		}
		return nullptr;
	}
}
