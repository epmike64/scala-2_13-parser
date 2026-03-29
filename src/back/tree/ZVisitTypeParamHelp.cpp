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

	void ZVisitTypeParamHelp::visitFunTypeParamClause(sp<fFunTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunTypeParamClause: " << n->toString() << std::endl;

		sp<ZTypeParamList> zDef = initScopeSymbol<ZTypeParamList>(prnSc);

		for (auto typeParam: n->getTypeParamList()) {
			esc subSc = visitChildNode(typeParam, prnSc, visitor);
			zDef->addTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {

		sp<ZVariantTypeParamList> zDef = initScopeSymbol<ZVariantTypeParamList>(prnSc);

		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			esc subSc = visitChildNode(variantTypeParam, prnSc, visitor);
			zDef->addVariantTypeParam(dynSp<ZVariantTypeParam>(subSc->getZSymbol()));
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;

		sp<ZVariantTypeParam> zDef = initScopeSymbol<ZVariantTypeParam>(prnSc, n->getVariance());

		esc subSc = visitChildNode(n->getTypeParam(), prnSc, visitor);
		zDef->setTypeParam(dynSp<ZTypeParam>(subSc->getZSymbol()));
	}


	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> zDef = initScopeSymbol<ZTypeParam>(prnSc, n->getIdentName());

		if (n->getTypeParamClause()) {
			esc subSc = visitChildNode(n->getTypeParamClause(), prnSc, visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(subSc->getZSymbol()));
		}
	}

}
