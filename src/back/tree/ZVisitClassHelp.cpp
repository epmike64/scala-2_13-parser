#include "back/tree/ZVisitClassHelp.hpp"

#include <iostream>

#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fClassConstr.hpp"
#include "ast/leaf/fClassDef.hpp"
#include "ast/leaf/fClassParents.hpp"
#include "ast/leaf/fClassTemplate.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fObjectDef.hpp"
#include "ast/leaf/fTemplate.hpp"
#include "ast/leaf/fTemplateBody.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "back/tree/ZVisitPSubTreeHelp.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"
#include "util/fUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;
	using namespace ast;

	void ZVisitClassHelp::visitClassDef(sp<fClassDef> cls, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (cls->isCaseClass() ? "Case " : "") << "ClassDef " << cls->getIdentName() <<
				std::endl;

		sp<ZClassDef> zClsDef = ms<ZClassDef>(cls->getIdentName());
		sp<ZStmtList> zClsDefStmts = std::dynamic_pointer_cast<ZStmtList>(prnSc->getZSymbol());
		zClsDefStmts->addStmt(zClsDef);
		esc clsDefScp = ms<ZEnclScope>(prnSc, zClsDef);


		if (cls->getModifiers()) {
			cls->getModifiers()->accept(visitor, clsDefScp);
		}

		if (cls->getConstrAccessModifier()) {
			cls->getConstrAccessModifier()->accept(visitor, clsDefScp);
		}

		if (cls->getTypeParamClause()) {
			zClsDef->setVariantTypeParamList(ms<ZVariantTypeParamList>());
			esc vtpListScp = ms<ZEnclScope>(clsDefScp, zClsDef->getVariantTypeParamList());
			cls->getTypeParamClause()->accept(visitor, vtpListScp);
		}

		if (cls->getClassParamClauses()) {
			zClsDef->setClassParamList(ms<ZClassParamList>());
			esc cplScp = ms<ZEnclScope>(clsDefScp, zClsDef->getClassParamList());
			cls->getClassParamClauses()->accept(visitor, cplScp);
		}

		if (cls->getExtendsTemplate()) {
			cls->getExtendsTemplate()->accept(visitor, clsDefScp);
		}
	}

	void ZVisitClassHelp::visitTraitDef(sp<fTraitDef> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Trait Definition: " << std::endl;

		sp<ZTraitDef> zTraiDef = ms<ZTraitDef>(n->getIdentName());
		esc traitScp = ms<ZEnclScope>(prnSc, zTraiDef);

		if (n->getModifiers()) {
			n->getModifiers()->accept(visitor, prnSc);
		}

		if (n->getTypeParamClause()) {
			zTraiDef->setVariantTypeParamList(ms<ZVariantTypeParamList>());
			esc vtpListScp = ms<ZEnclScope>(traitScp, zTraiDef->getVariantTypeParamList());
			n->getTypeParamClause()->accept(visitor, vtpListScp);
		}

		if (n->getExtendsTemplate()) {
			n->getExtendsTemplate()->accept(visitor, traitScp);
		}
	}

	void ZVisitClassHelp::visitObjectDef(sp<fObjectDef> obj, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (obj->isCaseObj() ? "Case " : "") << "Object" << obj->getIdentName() << std::endl;

		sp<ZObjectDef> zObjDef = ms<ZObjectDef>(obj->isCaseObj(), obj->getIdentName());
		esc objDefScp = ms<ZEnclScope>(prnSc, zObjDef);


		if (obj->getModifiers()) {
			sp<ZModifiers> mods = ms<ZModifiers>();
			esc modsScp = ms<ZEnclScope>(prnSc, mods);
			obj->getModifiers()->accept(visitor, modsScp);
			zObjDef->setModifiers(mods);
		}

		if (obj->getExtendsTemplate()) {
			obj->getExtendsTemplate()->accept(visitor, objDefScp);
		}
	}

	void ZVisitClassHelp::visitClassTemplate(sp<fClassTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Template" << std::endl;

		sp<ITemplateBody> tb = dynSp<ITemplateBody>(prnSc->getZSymbol());
		sp<ZClassTemplate> zCT = ms<ZClassTemplate>();
		tb->setTemplateBody(zCT);
		esc classTempScp = ms<ZEnclScope>(prnSc, zCT);

		sp<ZClassParents> zClsParents = ms<ZClassParents>();
		zCT->setClassParents(zClsParents);
		esc clsParentsScp = ms<ZEnclScope>(prnSc, zClsParents);
		n->getClassParents()->accept(visitor, clsParentsScp);


		n->getTemplateBody()->accept(visitor, classTempScp);
	}


	void ZVisitClassHelp::visitClassParents(sp<fClassParents> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parents" << std::endl;

		n->getConstr()->accept(visitor, prnSc);

		if (n->getWithTypes()) {
			std::cout << "Visiting With Types in Class Parents" << std::endl;
			n->getWithTypes()->accept(visitor, prnSc);
		}
	}

	void ZVisitClassHelp::visitClassConstr(sp<fClassConstr> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Constructor" << std::endl;

		ZVisitPSubTreeHelp::visitIntoSubTree(n->getParamType(), prnSc, visitor);
		if (n->getArgs()) {
			std::cout << "Visiting Constructor Arguments" << std::endl;
			ZVisitPSubTreeHelp::visitIntoSubTree(n->getArgs(), prnSc, visitor);
		}
	}


	void ZVisitClassHelp::visitTemplate(sp<fTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template" << std::endl;
		sp<ITemplateBody> tb = dynSp<ITemplateBody>(prnSc->getZSymbol());
		sp<ZClassTemplate> zCT = ms<ZClassTemplate>();
		tb->setTemplateBody(zCT);
		esc classTempScp = ms<ZEnclScope>(prnSc, zCT);
		n->getTemplateBody()->accept(visitor, classTempScp);
	}

	void ZVisitClassHelp::visitTemplateBody(sp<fTemplateBody> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template Body" << std::endl;

		sp<ZTemplateBody> zTb = dynSp<ZTemplateBody>(prnSc->getZSymbol());
		esc tbScp = ms<ZEnclScope>(prnSc, zTb);


		for (const auto& stmt : n->getStmts()) {
			zaccert(!stmt->isOperator(), "Statements in a block should not be operators");
			switch (dynSp<fLangOprnd>(stmt)->getLangOprndType()) {
				case LOprndT::PROD_SUB_TREE_N: {
					sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>();
					zTb->addStmt(pSubTr);
					esc pSubTrScp = ms<ZEnclScope>(tbScp, pSubTr);
					stmt->accept(visitor, pSubTrScp);
					continue;
				}
				default:
					break;
			}
			stmt->accept(visitor, tbScp);
		}
	}


	void ZVisitClassHelp::visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Block" << std::endl;

		sp<ZBlock> block = ms<ZBlock>();
		esc blockScp = ms<ZEnclScope>(prnSc, block);

		for (const auto& stmt : n->getStmts()) {
			zaccert(!stmt->isOperator(), "Statements in a block should not be operators");
			switch (dynSp<fLangOprnd>(stmt)->getLangOprndType()) {
				case LOprndT::PROD_SUB_TREE_N: {
					sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>();
					block->addStmt(pSubTr);
					esc pSubTrScp = ms<ZEnclScope>(blockScp, pSubTr);
					stmt->accept(visitor, pSubTrScp);
					continue;
				}
				default:
					break;
			}
			stmt->accept(visitor, blockScp);
		}
	}









}
