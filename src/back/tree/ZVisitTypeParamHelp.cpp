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

	void ZVisitTypeParamHelp::visitFunTypeParamClause(sp<fFunTypeParamClause> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunTypeParamClause: " << n->toString() << std::endl;

		sp<ZTypeParamList> zDef = initScopeSymbol<ZTypeParamList>(prnSc);

		for (auto typeParam: n->getTypeParamList()) {
			sbx subSc = visitChildNode(typeParam, visitor);
			zDef->addTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, sbx prnSc, sp<fAstNodVisitor> visitor) {

		sp<ZVariantTypeParamList> zDef = initScopeSymbol<ZVariantTypeParamList>(prnSc);

		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			sbx subSc = visitChildNode(variantTypeParam, visitor);
			zDef->addVariantTypeParam(dynSp<ZVariantTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;

		sp<ZVariantTypeParam> zDef = initScopeSymbol<ZVariantTypeParam>(prnSc, n->getVariance());

		sbx subSc = visitChildNode(n->getTypeParam(), visitor);
		zDef->setTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
	}


	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, sbx prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> zDef = initScopeSymbol<ZTypeParam>(prnSc, n->getIdentName());

		if (n->getTypeParamClause()) {
			sbx subSc = visitChildNode(n->getTypeParamClause(), visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(subSc->getZSymbol()));
		}
	}

}
