#include "back/tree/ZVisitFuncHelp.hpp"

#include <iostream>

#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fRegFunc.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZSymbol.hpp"


namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitFuncHelp::visitFunSig(sp<fFunSig> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunSig: " << n->getIdentName() << std::endl;

		assert(prnSc->getLangConstruct() == Z_REG_FUNC_DEF);

		if (n->getTypeParamList()) {
			for (auto tpp :*n->getTypeParamList()) {
				tpp->accept(visitor, prnSc);
			}
		}
		if (n->getParamClauses()) {
			n->getParamClauses()->accept(visitor, prnSc);
		}
	}

	void ZVisitFuncHelp::visitRegFunc(sp<fRegFunc> fun, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Regular Function: " << fun->getFunSig()->getIdentName() << std::endl;

		sp<ZRegFunc> zFunc = ms<ZRegFunc>(fun->getFunSig()->getIdentName());
		esc zFunScp = ms<ZEnclScope>(prnSc,  zFunc);

		if (fun->getModifiers()) {
			fun->getModifiers()->accept(visitor, zFunScp);
		}

		fun->getFunSig()->accept(visitor, zFunScp);

		if (fun->getReturnType()) {
			fun->getReturnType()->accept(visitor, zFunScp);
		}

		if (fun->getFunBody()) {
			fun->getFunBody()->accept(visitor, zFunScp);
		}
	}

}
