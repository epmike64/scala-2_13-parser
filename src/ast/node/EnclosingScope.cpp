#include "ast/node/EnclosingScope.hpp"

namespace zebra::ast::node {

	EnclosingScope::EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd)
	: parentScope_(std::move(parentScope)), parentScopeGrmrProd_(parentScopeGrmrProd) {}

	fLangGrmrProdE EnclosingScope::getParentScopeGrmrProd() const {
		return parentScopeGrmrProd_;
	}

	esc EnclosingScope::getParentScope() const {
		return parentScope_;
	}

	void EnclosingScope::setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) {
		this->polishCalcStack = std::move(astRPN);
	}

	sp<std::vector<sp<fAstNod>>> EnclosingScope::getPolishSS() const {
		return polishCalcStack;
	}

	void EnclosingScope::addValueDeclr(const std::string& name, sp<fLangValueDeclr> declr) {
		if (valueDeclrMap_ == nullptr) {
			valueDeclrMap_ = util::ms<std::unordered_map<std::string, sp<fLangValueDeclr>>>();
		}
		(*valueDeclrMap_)[name] = declr;
	}

	sp<fLangValueDeclr> EnclosingScope::getValueDeclr(const std::string& name) const {
		if (valueDeclrMap_ == nullptr) {
			return nullptr;
		}
		auto it = valueDeclrMap_->find(name);
		if (it != valueDeclrMap_->end()) {
			return it->second;
		}
		return nullptr;
	}

}