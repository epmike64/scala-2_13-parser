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
		if (!list) {
			throw std::runtime_error("visitFunTypeParamClause: parent scope must contain a ZTypeParamList");
		}

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

		sp<ZVariantTypeParamList> list = dynSp<ZVariantTypeParamList>(prnSc->getZSymbol());
		sp<ZVariantTypeParam> vtp = ms<ZVariantTypeParam>(n->getVariance());
		list->addVariantTypeParam(vtp);

		vtp->setTypeParam(ms<ZTypeParam>(n->getTypeParam()->getIdentName()));
		esc tpScp = ms<ZEnclScope>(prnSc, vtp->getTypeParam());

		n->getTypeParam()->accept(visitor, tpScp);
	}


	void ZVisitTypeParamHelp::visitTypeParam(sp<fTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Type Parameter: " << n->getIdentToken()->toString() << std::endl;

		sp<ZTypeParam> tp = dynSp<ZTypeParam>(prnSc->getZSymbol());

		if (n->getTypeParamClause()) {
			tp->setVariantTypeParamList(ms<ZVariantTypeParamList>());
			esc vtpListScp = ms<ZEnclScope>(prnSc, tp->getVariantTypeParamList());
			n->getTypeParamClause()->accept(visitor, vtpListScp);
		}
	}

}