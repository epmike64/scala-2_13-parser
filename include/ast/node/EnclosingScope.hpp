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
		sp<std::stack<util::sp<fLangTrBranch>>> lbrSS_;
	public:
		EnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setLbrSS(sp<std::stack<sp<fLangTrBranch>>>&& lbrSS) ;
		sp<std::stack<sp<fLangTrBranch>>> getLbrSS() const ;

	};



	//esc
}
