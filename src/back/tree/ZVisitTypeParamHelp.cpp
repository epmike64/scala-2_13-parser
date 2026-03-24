#include "back/tree/ZVisitTypeParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/leaf/fTypeParamClause.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			variantTypeParam->accept(visitor, prnSc);
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;
		// sp<fTypeParam> typeParam = std::dynamic_pointer_cast<fTypeParam>(n);
		// if (prnSc->getLangConstruct() == Z_REG_FUNC_DEF || prnSc->getLangConstruct() == Z_CLASS_DEF || prnSc->getLangConstruct() == Z_TRAIT_DEF) {
		//
		// 	sp<ZVariantTypeParam> zTP = ms<ZVariantTypeParam>(n->getVariance());
		// 	esc tpScp = ms<ZEnclScope>(prnSc, zTP);
		// 	typeParam->accept(visitor, tpScp);
		// 	sp<ZTypeParamList> list = std::dynamic_pointer_cast<ZTypeParamList>(prnSc->getZSymbol());
		// 	list->addTypeParam(zTP);
		//
		// } else {
		// 	typeParam->accept(visitor, prnSc);
		// }

		sp<ZTypeParam> typeParam = ms<ZTypeParam>(n->getTypeParam()->getIdentName());
		esc tpScp = ms<ZEnclScope>(prnSc, typeParam);
		n->getTypeParam()->accept(visitor, tpScp);
		sp<ZTypeParamList> list = std::dynamic_pointer_cast<ZTypeParamList>(prnSc->getZSymbol());
		list->addTypeParam(typeParam);

	}

	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;
		if (n->getTypeParamClause()) {
			n->getTypeParamClause()->accept(visitor, prnSc);
		}
	}

}