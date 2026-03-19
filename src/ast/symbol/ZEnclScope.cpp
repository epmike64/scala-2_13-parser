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

	void ZEnclScope::addSymbol(sp<ZSymbol> s) {
		if (symbolMap_ == nullptr) {
			symbolMap_ = ms<std::unordered_map<ZId, sp<ZSymbol>>>();
		}
		auto it = symbolMap_->find(s->zId());
		if (it != symbolMap_->end()) {
			throw std::runtime_error("Symbol with ID " + s->zId().qualId() + " already exists in the current scope");
		}
		(*symbolMap_)[s->zId()] = s;
	}

	sp<ZSymbol> ZEnclScope::getSymbol(const ZId zid) {
		if (symbolMap_ == nullptr) {
			return nullptr;
		}
		auto it = symbolMap_->find(zid);
		if (it != symbolMap_->end()) {
			return it->second;
		}
		return nullptr;
	}
}
