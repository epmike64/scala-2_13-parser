#pragma once

#include <vector>

#include "EnclsScopeFwd.hpp"
#include "fAstProdSubTreeN.hpp"
#include "fLangTree.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::node {


	class EnclosingScope {
		const esc parentScope_;
		const fLangGrmrProdE parentScopeGrmrProd_;
		sp<std::vector<sp<fAstNod>>> polishCalcSS;  //Reverse Polish notation (RPN)
	public:
		EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishCalcStack(sp<std::vector<sp<fAstNod>>>&& astRPN) ;

		sp<std::vector<sp<fAstNod>>> getPolishCalcStack() const;
	};



	//esc
}
