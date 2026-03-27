#include "back/tree/ZVisitParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"

namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitParamHelp::visitClassParamClauses(sp<fClassParamClauses> n, esc prnSc, sp<fAstNodVisitor> visitor) {

		for (const auto &classParamList: n->getClassParamLists()) {
			for (const auto &classParam: classParamList) {
				classParam->accept(visitor, prnSc);
			}
		}
		for (const auto &implicitClassParam: n->getImplicitClassParamList()) {
			implicitClassParam->accept(visitor, prnSc);
		}
	}



	void ZVisitParamHelp::visitClassParam(sp<fClassParam> clsPar, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parameter: " << clsPar->getIdentName() << std::endl;

		sp<ZClassParamList> classParamList = util::dynSp<ZClassParamList>(prnSc->getZSymbol());
		sp<ZClassParam> clsParam = ms<ZClassParam>(clsPar->getIdentName(), clsPar->isMutable());
		classParamList->addClassParam(clsParam);

		esc clsParamScp = ms<ZEnclScope>(prnSc, clsParam);
		clsPar->getParamType()->accept(visitor, clsParamScp);

		sp<fAstProdSubTreeN> assignExpr = clsPar->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>(Z_CLASS_PARAM_DEFAULT_EXPR);
			esc pSubTrScp = ms<ZEnclScope>(prnSc, pSubTr);

			assignExpr->accept(visitor, pSubTrScp);
			clsParam->setDefaultValueExpr(pSubTr->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParam(sp<fParam> par, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << par->getIdentName() << std::endl;

		assert(prnSc->getLangConstruct() == Z_REG_FUNC_DEF || prnSc->getLangConstruct() == Z_THIS_FUNC_DEF);
		sp<ZParam> zParam = ms<ZParam>(par->getIdentName());

		esc zParamScp = ms<ZEnclScope>(prnSc, zParam);
		par->getParamType()->accept(visitor, zParamScp);

		sp<fAstProdSubTreeN> assignExpr = par->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> zPSubTr = ms<ZProdSubTreeN>(Z_PARAM_DEFAULT_EXPR);
			esc zPSubTrScp = ms<ZEnclScope>(prnSc, zPSubTr);

			assignExpr->accept(visitor, zPSubTrScp);
			zParam->setDefaultValueExpr(zPSubTr->getTreePostOrderSS());
		}

		sp<ZFunc> f = std::dynamic_pointer_cast<ZFunc>(prnSc->getZSymbol());
		f->addParam(zParam);
	}

	void ZVisitParamHelp::visitParamTypes(sp<fParamTypes> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter Types" << std::endl;
		for (const auto& paramType: *n->getParamTypes()) {
			paramType->accept(visitor, prnSc);
		}
	}

}
