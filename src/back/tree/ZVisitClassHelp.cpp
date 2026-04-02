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
#include "ast/symbol/ZSymbolBox.hpp"
#include "back/tree/ZVisitPSubTreeHelp.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"
#include "util/fUtil.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;
	using namespace ast;

	void ZVisitClassHelp::visitClassDef(sp<fClassDef> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (n->isCaseClass() ? "Case " : "") << "ClassDef " << n->getIdentName() <<
				std::endl;

		sp<ZClassDef> zDef = initScopeSymbol<ZClassDef>(prnSbx, n->getIdentName());

		if (n->getModifiers()) {
			sbx symBx = visitChildNode(n->getModifiers(), visitor);
			zDef->setModifiers(dynSp<ZModifiers>(symBx->getZSymbol()));
		}

		if (n->getConstrAccessModifier()) {
			sbx symBx = visitChildNode(n->getConstrAccessModifier(), visitor);
			zDef->setConstrAccessModifier(dynSp<ZAccessModifier>(symBx->getZSymbol()));
		}

		if (n->getTypeParamClause()) {
			sbx symBx = visitChildNode(n->getTypeParamClause(), visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(symBx->getZSymbol()));
		}

		if (n->getClassParamClauses()) {
			sbx symBx = visitChildNode(n->getClassParamClauses(), visitor);
			zDef->setClassParamList(dynSp<ZClassParamList>(symBx->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			sbx symBx = visitChildNode(n->getExtendsTemplate(), visitor);

			switch (n->getExtendsTemplate()->getLangOprndType()) {
				case fLangOprndType::CLASS_TEMPLATE: {
					zDef->setClassTemplate(dynSp<ZClassTemplate>(symBx->getZSymbol()));
					break;
				}
				case fLangOprndType::TEMPLATE: {
					zDef->setClassTemplate(ms<ZClassTemplate>(nullptr, dynSp<ZTemplateBody>(symBx->getZSymbol())));
					break;
				}
				default: {
					std::cout << "Class extends an unknown template type" << std::endl;
					throw std::runtime_error("unknown template type");
				}
			}
		}
	}

	void ZVisitClassHelp::visitObjectDef(sp<fObjectDef> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (n->isCaseObj() ? "Case " : "") << "Object" << n->getIdentName() << std::endl;

		sp<ZObjectDef> zDef = initScopeSymbol<ZObjectDef>(prnSbx, n->isCaseObj(), n->getIdentName());

		if (n->getModifiers()) {
			sbx symBx = visitChildNode(n->getModifiers(), visitor);
			zDef->setModifiers(dynSp<ZModifiers>(symBx->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			sbx symBx = visitChildNode(n->getExtendsTemplate(), visitor);
			switch (n->getExtendsTemplate()->getLangOprndType()) {
				case fLangOprndType::CLASS_TEMPLATE: {
					zDef->setClassTemplate(dynSp<ZClassTemplate>(symBx->getZSymbol()));
					break;
				}
				case fLangOprndType::TEMPLATE: {
					zDef->setClassTemplate(ms<ZClassTemplate>(nullptr, dynSp<ZTemplateBody>(symBx->getZSymbol())));
					break;
				}
				default: {
					std::cout << "Class extends an unknown template type" << std::endl;
					throw std::runtime_error("unknown template type");
				}
			}
		}
	}

	void ZVisitClassHelp::visitTraitDef(sp<fTraitDef> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Trait Definition: " << std::endl;

		sp<ZTraitDef> zDef = initScopeSymbol<ZTraitDef>(prnSbx, n->getIdentName());

		if (n->getModifiers()) {
			sbx symBx = visitChildNode(n->getModifiers(), visitor);
			zDef->setModifiers(dynSp<ZModifiers>(symBx->getZSymbol()));
		}

		if (n->getTypeParamClause()) {
			sbx symBx = visitChildNode(n->getTypeParamClause(), visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(symBx->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			sbx symBx = visitChildNode(n->getExtendsTemplate(), visitor);
			zDef->setTemplateBody(dynSp<ZTemplateBody>(symBx->getZSymbol()));
		}
	}


	void ZVisitClassHelp::visitClassTemplate(sp<fClassTemplate> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Template" << std::endl;

		sp<ZClassTemplate> zDef = initScopeSymbol<ZClassTemplate>(prnSbx);

		sbx symBx = visitChildNode(n->getClassParents(), visitor);
		zDef->setClassParents(dynSp<ZClassParents>(symBx->getZSymbol()));

		if (n->getTemplateBody()) {
			sbx symBx = visitChildNode(n->getTemplateBody(), visitor);
			zDef->setTemplateBody(dynSp<ZTemplateBody>(symBx->getZSymbol()));
		}
	}


	void ZVisitClassHelp::visitClassParents(sp<fClassParents> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parents" << std::endl;

		sp<ZClassParents> zDef = initScopeSymbol<ZClassParents>(prnSbx);
		sbx symBx = visitChildNode(n->getConstr(),  visitor);
		zDef->setClassConstr(dynSp<ZClassConstr>(symBx->getZSymbol()));

		if (n->getWithType()) {
			std::cout << "Visiting With Types in Class Parents" << std::endl;
			sp<ZParamType> withType = ms<ZParamType>();
			sbx symBx = visitChildNode(n->getWithType(),  visitor);
			zDef->setWithType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitClassHelp::visitClassConstr(sp<fClassConstr> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Constructor" << std::endl;

		sp<ZClassConstr> zDef = initScopeSymbol<ZClassConstr>(prnSbx);
		sbx subSc = visitChildNode(n->getParamType(),  visitor);
		zDef->setParamType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());

		if (n->getArgs()) {
			std::cout << "Visiting Constructor Arguments" << std::endl;
			sbx subSc = visitChildNode(n->getArgs(),  visitor);
			zDef->setArgs(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}


	void ZVisitClassHelp::visitTemplate(sp<fTemplate> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template" << std::endl;
		n->getTemplateBody()->accept(visitor, prnSbx);
	}

	void ZVisitClassHelp::visitTemplateBody(sp<fTemplateBody> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template Body" << std::endl;

		sp<ZTemplateBody> zDef = initScopeSymbol<ZTemplateBody>(prnSbx);

		for (const auto& stmt : n->getStmts()) {
			sp<ast::fLangOprnd> langOprnd = std::dynamic_pointer_cast<ast::fLangOprnd>(stmt);
			sbx subSc = visitChildNode(langOprnd,  visitor);
			zDef->addStmt(dynSp<ZSymbol>(subSc->getZSymbol()));
			subSc->setZSymbol(nullptr); // Clear the symbol from the child scope after adding it to the template body
		}
	}


	void ZVisitClassHelp::visitBlock(sp<fBlock> n, sbx prnSbx, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Block" << std::endl;
		zaccert(prnSbx->getZSymbol() == nullptr, "Parent symbol in scope should be null when visiting a block");


		sp<ZBlock> zDef = ms<ZBlock>();
		prnSbx->setZSymbol(zDef);

		for (const auto& stmt : n->getStmts()) {
			sbx subSc = ms<ZSymbolBox>();
			stmt->accept(visitor, subSc);
			zDef->addStmt(subSc->getZSymbol());
		}
	}
}
