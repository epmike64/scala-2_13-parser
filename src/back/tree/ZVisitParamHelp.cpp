#include "back/tree/ZVisitParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/symbol/ZSymScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitParamHelp::visitClassParamClauses(sp<fClassParamClauses> n, ssc prnSc, sp<fAstNodVisitor> visitor) {

		sp<ZClassParamList> zDef = initScopeSymbol<ZClassParamList>(prnSc);

		for (const auto &classParamList: n->getClassParamLists()) {
			for (const auto &classParam: classParamList) {
				ssc subSc = visitChildNode(classParam, visitor);
				zDef->addClassParam(dynSp<ZClassParam>(subSc->getZSymbol()));
			}
		}
		for (const auto &classParam: n->getImplicitClassParamList()) {
			ssc subSc = visitChildNode(classParam,  visitor);
			zDef->addClassParam(dynSp<ZClassParam>(subSc->getZSymbol()));
		}
	}



	void ZVisitParamHelp::visitClassParam(sp<fClassParam> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parameter: " << n->getIdentName() << std::endl;

		sp<ZClassParam> zDef = initScopeSymbol<ZClassParam>(prnSc, n->getIdentName(), n->isMutable());

		if (n->getParamType()) {
			ssc subSc = visitChildNode(n->getParamType(),  visitor);
			zDef->setParamType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getDefaultValueExpr()) {
			ssc subSc = visitChildNode(n->getDefaultValueExpr(),visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParam(sp<fParam> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << n->getIdentName() << std::endl;

		sp<ZParam> zDef = initScopeSymbol<ZParam>(prnSc, n->getIdentName());

		ssc subSc = visitChildNode(n->getParamType(),  visitor);
		zDef->setParamType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());


		if ( n->getDefaultValueExpr()) {
			ssc subSc = visitChildNode(n->getDefaultValueExpr(), visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParamTypes(sp<fParamTypes> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter Types" << std::endl;

		sp<ZParamTypeList> zDef = initScopeSymbol<ZParamTypeList>(prnSc);

		for (const auto& paramType: *n->getParamTypes()) {
			ssc subSc = visitChildNode(paramType,  visitor);
			zDef->addParamType(dynSp<ZParamType>(subSc->getZSymbol()));
		}
	}

}
