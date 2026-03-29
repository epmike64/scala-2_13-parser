#include "back/tree/ZVisitTypeParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fFunTypeParamClause.hpp"
#include "ast/leaf/fTypeParamClause.hpp"
#include "ast/symbol/ZSymScope.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitTypeParamHelp::visitFunTypeParamClause(sp<fFunTypeParamClause> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunTypeParamClause: " << n->toString() << std::endl;

		sp<ZTypeParamList> zDef = initScopeSymbol<ZTypeParamList>(prnSc);

		for (auto typeParam: n->getTypeParamList()) {
			ssc subSc = visitChildNode(typeParam, visitor);
			zDef->addTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, ssc prnSc, sp<fAstNodVisitor> visitor) {

		sp<ZVariantTypeParamList> zDef = initScopeSymbol<ZVariantTypeParamList>(prnSc);

		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			ssc subSc = visitChildNode(variantTypeParam, visitor);
			zDef->addVariantTypeParam(dynSp<ZVariantTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;

		sp<ZVariantTypeParam> zDef = initScopeSymbol<ZVariantTypeParam>(prnSc, n->getVariance());

		ssc subSc = visitChildNode(n->getTypeParam(), visitor);
		zDef->setTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
	}


	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, ssc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> zDef = initScopeSymbol<ZTypeParam>(prnSc, n->getIdentName());

		if (n->getTypeParamClause()) {
			ssc subSc = visitChildNode(n->getTypeParamClause(), visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(subSc->getZSymbol()));
		}
	}

}
