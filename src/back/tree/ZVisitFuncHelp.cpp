#include "back/tree/ZVisitFuncHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fRegFunc.hpp"
#include "ast/leaf/fThisFunc.hpp"
#include "ast/leaf/fConstrBlock.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/symbol/ZSymbol.hpp"
#include "back/tree/ZVisitUtil.hpp"


namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitFuncHelp::visitFunSig(sp<fFunSig> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunSig: " << n->getIdentName() << std::endl;

		std::string funcName = n->getIdentName();
		if ("_OPERATOR_" == n->getIdentName()) {
			funcName = n->getIdentToken()->getTKind()->getTkName();
		}
		sp<ZFunSig> zDef = initScopeSymbol<ZFunSig>(prnSbx, funcName);

		if (n->getFunTypeParamClause()) {
			sbx symBx = visitChildNode(n->getFunTypeParamClause(), visitor);
			zDef->setFunTypeParamList(dynSp<ZTypeParamList>(symBx->getZSymbol()));
		}

		if (n->getParamClauses()) {
			sbx symBx = visitChildNode(n->getParamClauses(), visitor);
			zDef->setParamClauses(dynSp<ZParamList>(symBx->getZSymbol()));
		}
	}

	void ZVisitFuncHelp::visitRegFunc(sp<fRegFunc> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Regular Function: " << n->getFunSig()->getIdentName() << std::endl;

		sp<ZRegFunc> zDef = initScopeSymbol<ZRegFunc>(prnSbx);

		if (n->getModifiers()) {
			sbx symBx = visitChildNode(n->getModifiers(), visitor);
			zDef->setModifiers(dynSp<ZModifiers>(symBx->getZSymbol()));
		}

		sbx symBx = visitChildNode(n->getFunSig(), visitor);
		zDef->setFunSig(dynSp<ZFunSig>(symBx->getZSymbol()));

		if (n->getReturnType()) {
			symBx = visitChildNode(n->getReturnType(), visitor);
			zDef->setReturnType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getFunBodyExpr()) {
			symBx = visitChildNode(n->getFunBodyExpr(), visitor);
			zDef->setFunBodyExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol()));

		} else if (n->getFunBodyBlock()) {
			symBx = visitChildNode(n->getFunBodyBlock(), visitor);
			zDef->setFunBodyBlock(dynSp<ZBlock>(symBx->getZSymbol()));
		}
	}


	void ZVisitFuncHelp::visitThisFunc(sp<fThisFunc> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting This Function" << std::endl;
		sp<ZThisFunc> zDef = initScopeSymbol<ZThisFunc>(prnSbx);
		if (n->getParamClauses()) {
			sbx symBx = visitChildNode(n->getParamClauses(), visitor);
			zDef->setParamClauses(dynSp<ZParamList>(symBx->getZSymbol()));
		}
		if (n->getConstrBlock()) {
			sbx symBx = visitChildNode(n->getConstrBlock(), visitor);
			zDef->setConstrBlock(dynSp<ZConstrBlock>(symBx->getZSymbol()));
		}
	}

}
