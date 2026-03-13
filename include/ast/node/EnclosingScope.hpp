#pragma once

#include <stack>

#include "EnclsScopeFwd.hpp"
#include "fAstProdSubTreeN.hpp"
#include "fLangTree.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::node {


	class EnclosingScope {
		esc parentScope_;
		sp<std::stack<util::sp<fLangTrBranch>>> lbrSS_;
		public:
		EnclosingScope() = default;
		virtual ~EnclosingScope() = default;

		void setParentScope(esc parentScope);
		esc getParentScope();
		void setLbrSS(sp<std::stack<sp<fLangTrBranch>>>&& lbrSS) ;
		sp<std::stack<sp<fLangTrBranch>>> getLbrSS() const ;

	};



	//esc
}
