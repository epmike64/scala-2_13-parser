#include "back/tree/ZVisitTypeParamHelp.hpp"


#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fFunTypeParamClause.hpp"
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

	void ZVisitTypeParamHelp::visitFunTypeParamClause(sp<fFunTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting FunTypeParamClause: " << n->toString() << std::endl;

		sp<ZTypeParamList> list = std::dynamic_pointer_cast<ZTypeParamList>(prnSc->getZSymbol());

		for (auto typeParam: n->getTypeParamList()) {

			sp<ZTypeParam> tp = ms<ZTypeParam>(typeParam->getIdentName());
			esc tpSc = ms<ZEnclScope>(prnSc, tp);
			typeParam->accept(visitor, tpSc);
			list->addTypeParam(tp);
		}
	}

	void ZVisitTypeParamHelp::visitTypeParamClause(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			variantTypeParam->accept(visitor, prnSc);
		}
	}

	void ZVisitTypeParamHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;

		sp<ZVariantTypeParam> vtp = ms<ZVariantTypeParam>(n->getVariance());
		vtp->setTypeParam(ms<ZTypeParam>(n->getTypeParam()->getIdentName()));
		esc tpScp = ms<ZEnclScope>(prnSc, vtp->getTypeParam());

		n->getTypeParam()->accept(visitor, tpScp);

		sp<ZVariantTypeParamList> list = std::dynamic_pointer_cast<ZVariantTypeParamList>(prnSc->getZSymbol());
		list->addVariantTypeParam(vtp);

	}

	void ZVisitTypeParamHelp::buildVariantTypeParamClause(sp<fTypeParamClause> typeParamClause, sp<ZVariantTypeParamList> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Building TypeParamClause: " << std::endl;
		esc vtpListScp = ms<ZEnclScope>(prnSc, n);
		typeParamClause->accept(visitor, vtpListScp);
	}

	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> tp = std::dynamic_pointer_cast<ZTypeParam>(prnSc->getZSymbol());

		if (n->getTypeParamClause()) {
			tp->setVariantTypeParamList(ms<ZVariantTypeParamList>());
			buildVariantTypeParamClause(n->getTypeParamClause(), tp->getVariantTypeParamList(), prnSc, visitor);
		}
	}

}