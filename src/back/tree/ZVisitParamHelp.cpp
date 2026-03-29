#include "back/tree/ZVisitParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/symbol/ZLangConstruct.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitParamHelp::visitClassParamClauses(sp<fClassParamClauses> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {

		sp<ZClassParamList> zDef = initScopeSymbol<ZClassParamList>(prnSbx);

		for (const auto &classParamList: n->getClassParamLists()) {
			for (const auto &classParam: classParamList) {
				sbx symBx = visitChildNode(classParam, visitor);
				zDef->addClassParam(dynSp<ZClassParam>(symBx->getZSymbol()));
			}
		}
		for (const auto &classParam: n->getImplicitClassParamList()) {
			sbx symBx = visitChildNode(classParam,  visitor);
			zDef->addClassParam(dynSp<ZClassParam>(symBx->getZSymbol()));
		}
	}



	void ZVisitParamHelp::visitClassParam(sp<fClassParam> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parameter: " << n->getIdentName() << std::endl;

		sp<ZClassParam> zDef = initScopeSymbol<ZClassParam>(prnSbx, n->getIdentName(), n->isMutable());

		if (n->getParamType()) {
			sbx symBx = visitChildNode(n->getParamType(),  visitor);
			zDef->setParamType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getDefaultValueExpr()) {
			sbx symBx = visitChildNode(n->getDefaultValueExpr(),visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParam(sp<fParam> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << n->getIdentName() << std::endl;

		sp<ZParam> zDef = initScopeSymbol<ZParam>(prnSbx, n->getIdentName());

		sbx symBx = visitChildNode(n->getParamType(),  visitor);
		zDef->setParamType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());


		if ( n->getDefaultValueExpr()) {
			sbx symBx = visitChildNode(n->getDefaultValueExpr(), visitor);
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitParamHelp::visitParamTypes(sp<fParamTypes> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter Types" << std::endl;

		sp<ZParamTypeList> zDef = initScopeSymbol<ZParamTypeList>(prnSbx);

		for (const auto& paramType: *n->getParamTypes()) {
			sbx symBx = visitChildNode(paramType,  visitor);
			zDef->addParamType(dynSp<ZParamType>(symBx->getZSymbol()));
		}
	}

}
