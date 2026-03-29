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
			zDef->setParamType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getDefaultValueExpr()) {
			esc subSc = visitChildNode(n->getDefaultValueExpr(), prnSc, visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParam(sp<fParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << n->getIdentName() << std::endl;

		sp<ZParam> zDef = initScopeSymbol<ZParam>(prnSc, n->getIdentName());

		esc subSc = visitChildNode(n->getParamType(), prnSc, visitor);
		zDef->setParamType(dynSp<ZParamType>(subSc->getZSymbol()));


		if ( n->getDefaultValueExpr()) {
			esc subSc = visitChildNode(n->getDefaultValueExpr(), prnSc, visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParamTypes(sp<fParamTypes> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter Types" << std::endl;

		sp<ZParamTypeList> zDef = initScopeSymbol<ZParamTypeList>(prnSc);

		for (const auto& paramType: *n->getParamTypes()) {
			esc subSc = visitChildNode(paramType, prnSc, visitor);
			zDef->addParamType(dynSp<ZParamType>(subSc->getZSymbol()));
		}
	}

}
