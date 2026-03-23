#include "back/tree/ZVisitFuncHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"
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
			sp<ZType> zType = ms<ZType>();
			esc typeScp = ms<ZEnclScope>(prnSc, zType);
			fun->getReturnType()->accept(visitor, typeScp);
			zFunc->setReturnType(zType);
		}

		if (fun->getFunBodyExpr()) {

			sp<ZProdSubTreeN> tr = ms<ZProdSubTreeN>();
			esc trScp = ms<ZEnclScope>(prnSc, tr);
			fun->getFunBodyExpr()->accept(visitor, trScp);
			zFunc->setFunBodyExpr(tr);

		} else if (fun->getFunBodyBlock()) {

			sp<ZBlock> block = ms<ZBlock>();
			esc zBlockScp = ms<ZEnclScope>(prnSc, block);
			fun->getFunBodyBlock()->accept(visitor, zBlockScp);
			zFunc->setFunBodyBlock(block);
		}
	}

}
