#include "back/tree/ZVisitTypeHelp.hpp"

#include <iostream>

#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fTypeParamClause.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"

namespace zebra::back::tree {

	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitTypeHelp::visitClassParamClauses(sp<fClassParamClauses> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		assert(prnSc->getZSymbol() != nullptr && prnSc->getLangConstruct() == Z_CLASS_DEF);

		for (const auto &classParamList: n->getClassParamLists()) {
			for (const auto &classParam: classParamList) {
				classParam->accept(visitor, prnSc);
			}
		}
		for (const auto &implicitClassParam: n->getImplicitClassParamList()) {
			implicitClassParam->accept(visitor, prnSc);
		}
	}

	void ZVisitTypeHelp::visitTypeParamClauses(sp<fTypeParamClause> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		for (auto variantTypeParam: *n->getVariantTypeParams()) {
			variantTypeParam->accept(visitor, prnSc);
		}
	}

	void ZVisitTypeHelp::visitVariantTypeParam(sp<fVariantTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;
		// sp<ZVariantTypeParam> vTp = ms<ZVariantTypeParam>();
		// esc vTpScp = ms<ZEnclScope>(prnSc,  vTp);
	}

	void ZVisitTypeHelp::visitTypeParam(sp<fTypeParam> n, esc prnSc, sp<fAstNodVisitor> visitor) {
	}

	void ZVisitTypeHelp::visitClassParam(sp<fClassParam> clsPar, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parameter: " << clsPar->getIdentName() << std::endl;
		assert(prnSc->getLangConstruct() == Z_CLASS_DEF);

		sp<ZClassParam> clsParam = ms<ZClassParam>(clsPar->getIdentName(), clsPar->isMutable());
		esc clsParamScp = ms<ZEnclScope>(prnSc, clsParam);
		clsPar->getParamType()->accept(visitor, clsParamScp);

		sp<fAstProdSubTreeN> assignExpr = clsPar->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>(Z_CLASS_PARAM_DEFAULT_EXPR);
			esc pSubTrScp = ms<ZEnclScope>(prnSc, pSubTr);

			assignExpr->accept(visitor, pSubTrScp);
			clsParam->setDefaultValueExpr(pSubTr->getTreePostOrderSS());
		}
		sp<ZClassDef> clsDef = std::dynamic_pointer_cast<ZClassDef>(prnSc->getZSymbol());
		clsDef->addClassParam(clsParam);
	}

	void ZVisitTypeHelp::visitParam(sp<fParam> par, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Parameter: " << par->getIdentName() << std::endl;

		assert(prnSc->getLangConstruct() == Z_REG_FUNC || prnSc->getLangConstruct() == Z_THIS_FUNC);
		sp<ZParam> zParam = ms<ZParam>(par->getIdentName());

		esc zParamScp = ms<ZEnclScope>(prnSc, zParam);
		par->getParamType()->accept(visitor, zParamScp);

		sp<fAstProdSubTreeN> assignExpr = par->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> zPSubTr = ms<ZProdSubTreeN>(Z_PARAM_DEFAULT_EXPR);
			esc zPSubTrScp = ms<ZEnclScope>(prnSc, zPSubTr);

			assignExpr->accept(visitor, zPSubTrScp);
			zParam->setDefaultValueExpr(zPSubTr->getTreePostOrderSS());
		}

		sp<ZFunc> f = std::dynamic_pointer_cast<ZFunc>(prnSc->getZSymbol());
		f->addParam(zParam);
	}
}
