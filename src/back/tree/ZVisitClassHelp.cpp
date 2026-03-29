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
#include "ast/symbol/ZSymScope.hpp"
#include "back/tree/ZVisitPSubTreeHelp.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"
#include "util/fUtil.hpp"
#include "back/tree/ZVisitUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;
	using namespace ast;

	void ZVisitClassHelp::visitClassDef(sp<fClassDef> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (n->isCaseClass() ? "Case " : "") << "ClassDef " << n->getIdentName() <<
				std::endl;

		sp<ZClassDef> zDef = initScopeSymbol<ZClassDef>(prnSc, n->getIdentName());

		if (n->getModifiers()) {
			esc subSc = visitChildNode(n->getModifiers(), prnSc, visitor);
			zDef->setModifiers(dynSp<ZModifiers>(subSc->getZSymbol()));
		}

		if (n->getConstrAccessModifier()) {
			esc subSc = visitChildNode(n->getConstrAccessModifier(), prnSc, visitor);
			zDef->setConstrAccessModifier(dynSp<ZAccessModifier>(subSc->getZSymbol()));
		}

		if (n->getTypeParamClause()) {
			esc subSc = visitChildNode(n->getTypeParamClause(), prnSc, visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(subSc->getZSymbol()));
		}

		if (n->getClassParamClauses()) {
			esc subSc = visitChildNode(n->getClassParamClauses(), prnSc, visitor);
			zDef->setClassParamList(dynSp<ZClassParamList>(subSc->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			esc subSc = visitChildNode(n->getExtendsTemplate(), prnSc, visitor);

			switch (n->getExtendsTemplate()->getLangOprndType()) {
				case fLangOprndType::CLASS_TEMPLATE: {
					zDef->setClassTemplate(dynSp<ZClassTemplate>(subSc->getZSymbol()));
					break;
				}
				case fLangOprndType::TEMPLATE: {
					zDef->setClassTemplate(ms<ZClassTemplate>(nullptr, dynSp<ZTemplateBody>(subSc->getZSymbol())));
					break;
				}
				default: {
					std::cout << "Class extends an unknown template type" << std::endl;
					throw std::runtime_error("unknown template type");
				}
			}
		}
	}

	void ZVisitClassHelp::visitObjectDef(sp<fObjectDef> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting " << (n->isCaseObj() ? "Case " : "") << "Object" << n->getIdentName() << std::endl;

		sp<ZObjectDef> zDef = initScopeSymbol<ZObjectDef>(prnSc, n->isCaseObj(), n->getIdentName());

		if (n->getModifiers()) {
			esc subSc = visitChildNode(n->getModifiers(), prnSc, visitor);
			zDef->setModifiers(dynSp<ZModifiers>(subSc->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			esc subSc = visitChildNode(n->getExtendsTemplate(), prnSc, visitor);
			switch (n->getExtendsTemplate()->getLangOprndType()) {
				case fLangOprndType::CLASS_TEMPLATE: {
					zDef->setClassTemplate(dynSp<ZClassTemplate>(subSc->getZSymbol()));
					break;
				}
				case fLangOprndType::TEMPLATE: {
					zDef->setClassTemplate(ms<ZClassTemplate>(nullptr, dynSp<ZTemplateBody>(subSc->getZSymbol())));
					break;
				}
				default: {
					std::cout << "Class extends an unknown template type" << std::endl;
					throw std::runtime_error("unknown template type");
				}
			}
		}
	}

	void ZVisitClassHelp::visitTraitDef(sp<fTraitDef> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Trait Definition: " << std::endl;

		sp<ZTraitDef> zDef = initScopeSymbol<ZTraitDef>(prnSc, n->getIdentName());

		if (n->getModifiers()) {
			esc subSc = visitChildNode(n->getModifiers(), prnSc, visitor);
			zDef->setModifiers(dynSp<ZModifiers>(subSc->getZSymbol()));
		}

		if (n->getTypeParamClause()) {
			esc subSc = visitChildNode(n->getTypeParamClause(), prnSc, visitor);
			zDef->setVariantTypeParamList(dynSp<ZVariantTypeParamList>(subSc->getZSymbol()));
		}

		if (n->getExtendsTemplate()) {
			esc subSc = visitChildNode(n->getExtendsTemplate(), prnSc, visitor);
			zDef->setTemplateBody(dynSp<ZTemplateBody>(subSc->getZSymbol()));
		}
	}


	void ZVisitClassHelp::visitClassTemplate(sp<fClassTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Template" << std::endl;

		sp<ZClassTemplate> zDef = initScopeSymbol<ZClassTemplate>(prnSc);

		esc subSc = visitChildNode(n->getClassParents(), prnSc, visitor);
		zDef->setClassParents(dynSp<ZClassParents>(subSc->getZSymbol()));

		if (n->getTemplateBody()) {
			esc subSc = visitChildNode(n->getTemplateBody(), prnSc, visitor);
			zDef->setTemplateBody(dynSp<ZTemplateBody>(subSc->getZSymbol()));
		}
	}


	void ZVisitClassHelp::visitClassParents(sp<fClassParents> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Parents" << std::endl;

		sp<ZClassParents> zDef = initScopeSymbol<ZClassParents>(prnSc);
		esc subSc = visitChildNode(n->getConstr(),  prnSc, visitor);
		zDef->setClassConstr(dynSp<ZClassConstr>(subSc->getZSymbol()));
		//
		// if (n->getWithTypes()) {
		// 	std::cout << "Visiting With Types in Class Parents" << std::endl;
		// 	n->getWithTypes()->accept(visitor, prnSc);
		// }
	}

	void ZVisitClassHelp::visitClassConstr(sp<fClassConstr> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Constructor" << std::endl;

		sp<ZClassConstr> zDef = initScopeSymbol<ZClassConstr>(prnSc);
		esc subSc = visitChildNode(n->getParamType(),  prnSc, visitor);
		zDef->setParamType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());

		if (n->getArgs()) {
			std::cout << "Visiting Constructor Arguments" << std::endl;
			esc subSc = visitChildNode(n->getArgs(),  prnSc, visitor);
			zDef->setArgs(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}


	void ZVisitClassHelp::visitTemplate(sp<fTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template" << std::endl;
		n->getTemplateBody()->accept(visitor, prnSc);
	}

	void ZVisitClassHelp::visitTemplateBody(sp<fTemplateBody> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template Body" << std::endl;

		sp<ZTemplateBody> zDef = initScopeSymbol<ZTemplateBody>(prnSc);

		for (const auto& stmt : n->getStmts()) {
			sp<ast::fLangOprnd> langOprnd = std::dynamic_pointer_cast<ast::fLangOprnd>(stmt);
			esc subSc = visitChildNode(langOprnd,  prnSc, visitor);
			zDef->addStmt(dynSp<ZSymbol>(subSc->getZSymbol()));
			subSc->setZSymbol(nullptr); // Clear the symbol from the child scope after adding it to the template body
		}
	}


	void ZVisitClassHelp::visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Block" << std::endl;
		zaccert(prnSc->getZSymbol() == nullptr, "Parent symbol in scope should be null when visiting a block");


		sp<ZBlock> zDef = ms<ZBlock>();
		prnSc->setZSymbol(zDef);

		for (const auto& stmt : n->getStmts()) {
			esc subSc = ms<ZSymScope>(prnSc);
			stmt->accept(visitor, subSc);
			zDef->addStmt(subSc->getZSymbol());
		}
	}
}
