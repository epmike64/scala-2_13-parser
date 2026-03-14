#include "ast/symbol/ZEnclosingScope.hpp"

namespace zebra::ast::symbol {

	ZEnclosingScope::ZEnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd)
	: parentScope_(std::move(parentScope)), parentScopeGrmrProd_(parentScopeGrmrProd) {}

	fLangGrmrProdE ZEnclosingScope::getParentScopeGrmrProd() const {
		return parentScopeGrmrProd_;
	}

	esc ZEnclosingScope::getParentScope() const {
		return parentScope_;
	}

	void ZEnclosingScope::setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) {
		this->polishCalcStack = std::move(astRPN);
	}

	sp<std::vector<sp<fAstNod>>> ZEnclosingScope::getPolishSS() const {
		return polishCalcStack;
	}

	void ZEnclosingScope::addSymbol(const std::string& name, sp<ZSymbol> declr) {
		if (symbolMap_ == nullptr) {
			symbolMap_ = util::ms<std::unordered_map<std::string, sp<ZSymbol>>>();
		}
		(*symbolMap_)[name] = declr;
	}

	sp<ZSymbol> ZEnclosingScope::getSymbol(const std::string& name) const {
		if (symbolMap_ == nullptr) {
			return nullptr;
		}
		auto it = symbolMap_->find(name);
		if (it != symbolMap_->end()) {
			return it->second;
		}
		return nullptr;
	}

}