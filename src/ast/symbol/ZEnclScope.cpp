#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::ast::symbol {
	ZEnclScope::ZEnclScope(esc parentScope, ZGrmrProdE parentScopeGrmrProd)
		: parentScope_(std::move(parentScope)), parentScopeGrmrProd_(parentScopeGrmrProd) {
	}

	ZGrmrProdE ZEnclScope::getParentScopeGrmrProd() const {
		return parentScopeGrmrProd_;
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

	// void ZEnclScope::addTypeParamSymb(const std::string &name, sp<ZSymbol> typeParam) {
	// 	if (typeParamMap_ == nullptr) {
	// 		typeParamMap_ = ms<std::unordered_map<std::string, sp<std::vector<sp<ZSymbol> > > > >();
	// 	}
	// 	auto it = typeParamMap_->find(name);
	// 	if (it == typeParamMap_->end()) {
	// 		(*typeParamMap_)[name] = ms<std::vector<sp<ZSymbol> > >();
	// 	}
	// 	(*typeParamMap_)[name]->push_back(typeParam);
	// }
	//
	// PVecP<ZSymbol> ZEnclScope::getSymbol(const std::string &name) const {
	// 	if (symbolMap_ == nullptr) {
	// 		return nullptr;
	// 	}
	// 	auto it = symbolMap_->find(name);
	// 	if (it == symbolMap_->end()) {
	// 		return nullptr;
	// 	}
	// 	return it->second;
	// }
	//
	//
	// PVecP<ZTypeParam> ZEnclScope::getTypeParamSymb(const std::string &name) const {
	// }
}
