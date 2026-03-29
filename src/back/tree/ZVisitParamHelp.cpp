#include "back/tree/ZVisitParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitParamHelp::visitClassParamClauses(sp<fClassParamClauses> n, esc prnSc, sp<fAstNodVisitor> visitor) {

		sp<ZClassParamList> zDef = initScopeSymbol<ZClassParamList>(prnSc);

		for (const auto &classParamList: n->getClassParamLists()) {
			for (const auto &classParam: classParamList) {
				esc subSc = visitChildNode(classParam, prnSc, visitor);
				zDef->addClassParam(dynSp<ZClassParam>(subSc->getZSymbol()));
			}
		}
		for (const auto &classParam: n->getImplicitClassParamList()) {
			esc subSc = visitChildNode(classParam, prnSc, visitor);
			zDef->addClassParam(dynSp<ZClassParam>(subSc->getZSymbol()));
		}
	}



	void ZVisitParamHelp::visitClassParam(sp<fClassParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parameter: " << n->getIdentName() << std::endl;

		sp<ZClassParam> zDef = initScopeSymbol<ZClassParam>(prnSc, n->getIdentName(), n->isMutable());

		if (n->getParamType()) {
			esc subSc = visitChildNode(n->getParamType(), prnSc, visitor);
			zDef->setZParamType(dynSp<ZParamType>(subSc->getZSymbol()));
		}

		if (n->getDefaultValueExpr()) {
			esc subSc = visitChildNode(n->getDefaultValueExpr(), prnSc, visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParam(sp<fParam> par, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << par->getIdentName() << std::endl;

		assert(prnSc->getLangConstruct() == Z_REG_FUNC_DEF || prnSc->getLangConstruct() == Z_THIS_FUNC_DEF);
		sp<ZParam> zParam = ms<ZParam>(par->getIdentName());

		esc zParamScp = ms<ZEnclScope>(prnSc);
		zParamScp->setZSymbol(zParam);
		par->getParamType()->accept(visitor, zParamScp);

		sp<fAstProdSubTreeN> assignExpr = par->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> zPSubTr = ms<ZProdSubTreeN>(Z_PARAM_DEFAULT_EXPR);
			esc zPSubTrScp = ms<ZEnclScope>(prnSc);
			zPSubTrScp->setZSymbol(zPSubTr);

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
