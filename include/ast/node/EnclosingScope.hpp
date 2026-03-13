#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "EnclsScopeFwd.hpp"
#include "fAstProdSubTreeN.hpp"
#include "fLangTree.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::node {

	class fLangValueDeclr {

	};

	class EnclosingScope {
		const esc parentScope_;
		const fLangGrmrProdE parentScopeGrmrProd_;
		sp<std::vector<sp<fAstNod>>> polishCalcSS;
		sp<std::unordered_map<std::string, sp<fLangValueDeclr>>> valueDeclrMap_;
	public:
		EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishCalcStack(sp<std::vector<sp<fAstNod>>>&& astRPN) ;

		sp<std::vector<sp<fAstNod>>> getPolishCalcStack() const;

		void addValueDeclr(const std::string& name, sp<fLangValueDeclr> declr) {
			if (valueDeclrMap_ == nullptr) {
				valueDeclrMap_ = util::ms<std::unordered_map<std::string, sp<fLangValueDeclr>>>();
			}
			(*valueDeclrMap_)[name] = declr;
		}
	};



	//esc
}
