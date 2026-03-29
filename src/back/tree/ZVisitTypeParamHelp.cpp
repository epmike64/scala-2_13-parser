#include "back/tree/ZVisitTypeParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fFunTypeParamClause.hpp"
#include "ast/leaf/fTypeParamClause.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitTypeParamHelp::visitFunTypeParamClause(sp<fFunTypeParamClause> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunTypeParamClause: " << n->toString() << std::endl;

		sp<ZTypeParamList> zDef = initScopeSymbol<ZTypeParamList>(prnSbx);

		for (auto typeParam: n->getTypeParamList()) {
			sbx symBx = visitChildNode(typeParam, visitor);
			zDef->addTypeParam(dynSp<ZTypeParam>(symBx->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {

		sp<ZVariantTypeParamList> zDef = initScopeSymbol<ZVariantTypeParamList>(prnSbx);

		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			sbx symBx = visitChildNode(variantTypeParam, visitor);
			zDef->addVariantTypeParam(dynSp<ZVariantTypeParam>(symBx->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;

		sp<ZVariantTypeParam> zDef = initScopeSymbol<ZVariantTypeParam>(prnSbx, n->getVariance());

		sbx symBx = visitChildNode(n->getTypeParam(), visitor);
		zDef->setTypeParam(dynSp<ZTypeParam>(symBx->getZSymbol()));
	}


	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> zDef = initScopeSymbol<ZTypeParam>(prnSbx, n->getIdentName());

		if (n->getTypeParamClause()) {
			sbx symBx = visitChildNode(n->getTypeParamClause(), visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(symBx->getZSymbol()));
		}
	}

}
