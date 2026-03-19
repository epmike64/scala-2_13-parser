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

	void ZEnclScope::addSymbol(const std::string &name, sp<ZSymbol> declr) {
		if (symbolMap_ == nullptr) {
			symbolMap_ = ms<std::unordered_map<std::string, sp<std::vector<sp<ZSymbol> > > > >();
		}
		auto it = symbolMap_->find(name);
		if (it == symbolMap_->end()) {
			(*symbolMap_)[name] = ms<std::vector<sp<ZSymbol> > >();
		}
		(*symbolMap_)[name]->push_back(declr);
	}

	sp<ZSymbol> ZEnclScope::getSymbol(const std::string &name) {
		if (symbolMap_ == nullptr) {
			return nullptr;
		}
		auto it = symbolMap_->find(name);
		if (it == symbolMap_->end()) {
			return nullptr;
		}
		return !it->second->empty() ? it->second->back() : nullptr;

	}
}
