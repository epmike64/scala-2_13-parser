#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {

	ZEnclScope::ZEnclScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd)
	: parentScope_(std::move(parentScope)), parentScopeGrmrProd_(parentScopeGrmrProd) {}

	fLangGrmrProdE ZEnclScope::getParentScopeGrmrProd() const {
		return parentScopeGrmrProd_;
	}

	esc ZEnclScope::getParentScope() const {
		return parentScope_;
	}

	void ZEnclScope::setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) {
		this->polishCalcStack = std::move(astRPN);
	}

	sp<std::vector<sp<fAstNod>>> ZEnclScope::getPolishSS() const {
		return polishCalcStack;
	}

	void ZEnclScope::addSymbol(const std::string& name, sp<ZSymbol> declr) {
		if (symbVecMap_== nullptr) {
			symbVecMap_ = ms<std::unordered_map<std::string, sp<std::vector<sp<ZSymbol>>>>>();
		}
		auto it = symbVecMap_->find(name);
		if (it == symbVecMap_->end()) {
			(*symbVecMap_)[name] = ms<std::vector<sp<ZSymbol>>>();
		}
		(*symbVecMap_)[name]->push_back(declr);
	}

	PtrVec<ZSymbol> ZEnclScope::getSymbol(const std::string& name) const {
		if (symbVecMap_== nullptr) {
			return nullptr;
		}
		auto it = symbVecMap_->find(name);
		if (it == symbVecMap_->end()) {
			return nullptr;
		}
		return it->second;
	}

}