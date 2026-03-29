#include "back/tree/ZVisitFuncHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fRegFunc.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/symbol/ZSymbol.hpp"
#include "back/tree/ZVisitUtil.hpp"


namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitFuncHelp::visitFunSig(sp<fFunSig> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunSig: " << n->getIdentName() << std::endl;

		sp<ZFunSig> zDef = initScopeSymbol<ZFunSig>(prnSc, n->getIdentName());

		if (n->getFunTypeParamClause()) {
			sbx subSc = visitChildNode(n->getFunTypeParamClause(), visitor);
			zDef->setFunTypeParamList(dynSp<ZTypeParamList>(subSc->getZSymbol()));
		}

		if (n->getParamClauses()) {
			sbx subSc = visitChildNode(n->getParamClauses(), visitor);
			zDef->setParamClauses(dynSp<ZParamList>(subSc->getZSymbol()));
		}
	}

	void ZVisitFuncHelp::visitRegFunc(sp<fRegFunc> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Regular Function: " << n->getFunSig()->getIdentName() << std::endl;

		sp<ZRegFunc> zDef = initScopeSymbol<ZRegFunc>(prnSc);

		if (n->getModifiers()) {
			sbx subSc = visitChildNode(n->getModifiers(), visitor);
			zDef->setModifiers(dynSp<ZModifiers>(subSc->getZSymbol()));
		}

		sbx subSc = visitChildNode(n->getFunSig(), visitor);
		zDef->setFunSig(dynSp<ZFunSig>(subSc->getZSymbol()));

		if (n->getReturnType()) {
			subSc = visitChildNode(n->getReturnType(), visitor);
			zDef->setReturnType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getFunBodyExpr()) {
			subSc = visitChildNode(n->getFunBodyExpr(), visitor);
			zDef->setFunBodyExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol()));

		} else if (n->getFunBodyBlock()) {
			subSc = visitChildNode(n->getFunBodyBlock(), visitor);
			zDef->setFunBodyBlock(dynSp<ZBlock>(subSc->getZSymbol()));
		}
	}


	void ZVisitFuncHelp::visitThisFunc(sp<fThisFunc> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting This Function" << std::endl;
	}

}
