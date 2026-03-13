#pragma once

#include <stack>

#include "EnclsScopeFwd.hpp"
#include "fAstProdSubTreeN.hpp"
#include "fLangTree.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::node {


	class EnclosingScope {
		const esc parentScope_;
		const fLangGrmrProdE parentScopeGrmrProd_;
		sp<std::stack<sp<fAstNod>>> polishCalcSS;  //Reverse Polish notation (RPN)
	public:
		EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishCalcStack(sp<std::stack<sp<fAstNod>>>&& astRPN) ;

		sp<std::stack<sp<fAstNod>>> getPolishCalcStack() const;
	};



	//esc
}
