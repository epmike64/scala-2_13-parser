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
		sp<std::vector<sp<fAstNod>>> polishCalcStack; //RPN - reverse polish notation
		sp<std::unordered_map<std::string, sp<fLangValueDeclr>>> valueDeclrMap_;
	public:
		EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) ;

		sp<std::vector<sp<fAstNod>>> getPolishSS() const;

		void addValueDeclr(const std::string& name, sp<fLangValueDeclr> declr);
		sp<fLangValueDeclr> getValueDeclr(const std::string& name) const;
	};



	//esc
}
