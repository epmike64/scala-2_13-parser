
#include "back/tree/ZVisitor.hpp"

#include <iostream>

#include "ast/leaf/fAccessQualifier.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/leaf/fCaseClause.hpp"
#include "ast/leaf/fCaseClauses.hpp"
#include "ast/leaf/fClassParents.hpp"
#include "ast/leaf/fClassTemplate.hpp"
#include "ast/leaf/fConstrBlock.hpp"
#include "ast/leaf/fFor.hpp"
#include "ast/leaf/fGenerator.hpp"
#include "ast/leaf/fId.hpp"
#include "ast/leaf/fIds.hpp"
#include "ast/leaf/fLocalModifier.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fRegFunc.hpp"
#include "ast/leaf/fObjectDef.hpp"
#include "ast/leaf/fOverrideModifier.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/leaf/fReturn.hpp"
#include "ast/leaf/fTemplateBody.hpp"
#include "ast/leaf/fThisFunc.hpp"
#include "ast/leaf/fThrow.hpp"
#include "ast/leaf/fTry.hpp"
#include "ast/leaf/fTypeDef.hpp"
#include "ast/leaf/fTypeParam.hpp"
#include "ast/leaf/fUnderscore.hpp"
#include "ast/leaf/fValueDcl.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "back/tree/ZVisitClassHelp.hpp"
#include "back/tree/ZVisitFuncHelp.hpp"
#include "util/fUUID.hpp"
#include "back/tree/ZVisitPSubTreeHelp.hpp"
#include "back/tree/ZVisitParamHelp.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"
#include "back/tree/ZVisitUtil.hpp"
#include "util/fUtil.hpp"

namespace zebra::back::tree {


	void ZVisitor::visit() {
		std::cout << "--- Visitor starts ---" << std::endl;
		sp<ZSymbolBox> programSc = ms<ZSymbolBox>();
		zProgram_ = initScopeSymbol<ZProgram>(programSc, "_TestProgram_PROGRAM_");
		sbx symBx = visitChildNode(compileUnit_, shared_from_this());
		zProgram_->addCompileUnit(dynSp<ZCompileUnit>(symBx->getZSymbol()));
	}

	void ZVisitor::visit(sp<fCompileUnit> n, sbx prnSbx)  {

		sp<ZCompileUnit> zDef = initScopeSymbol<ZCompileUnit>(prnSbx, "_TestClass_COMPILE_UNIT_");

		if (n->getPackages().size() > 0) {
			std::string packgName;
			for (const auto& pkg : n->getPackages()) {
				packgName += pkg->getPackgQualName();
			}
			zDef->setPackage(packgName);
		}

		if (n->getStmts().size() > 0) {
			std::cout << "Visiting Statements in Compile Unit" << std::endl;
			for (const auto& stmt : n->getStmts()) {
				sp<ast::fLangOprnd> langOprnd = std::dynamic_pointer_cast<ast::fLangOprnd>(stmt);
				sbx symBx = visitChildNode(langOprnd,  shared_from_this());
				zDef->addStmt(dynSp<ZSymbol>(symBx->getZSymbol()));
			}
		}
	}

	void  ZVisitor::visit(sp<fClassDef> cls, sbx prnSbx){
		ZVisitClassHelp::visitClassDef(cls, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fObjectDef> obj, sbx prnSbx) {
		ZVisitClassHelp::visitObjectDef(obj, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassTemplate> n, sbx prnSbx) {
		ZVisitClassHelp::visitClassTemplate(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplate> n, sbx prnSbx) {
		ZVisitClassHelp::visitTemplate(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplateBody> n, sbx prnSbx) {
		ZVisitClassHelp::visitTemplateBody(n, prnSbx, shared_from_this());
	}


	void ZVisitor::visit(sp<fSelfType> n, sbx prnSbx) {
		std::cout << "Visiting Self Type" << std::endl;
		sp<ZSelfType> zDef = initScopeSymbol<ZSelfType>(prnSbx, n->getIdentName());
		if (n->getSelfType()) {
			sbx symBx = visitChildNode(n->getSelfType(),  shared_from_this());
			zDef->setSelfType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fParamClauses> n, sbx prnSbx) {

		sp<ZParamList> zDef = initScopeSymbol<ZParamList>(prnSbx);

		for (auto paramList : n->getParamLists()) {
			for (auto param : paramList) {
				sbx symBx = visitChildNode(param, shared_from_this());
				zDef->addParam(dynSp<ZParam>(symBx->getZSymbol()));
			}
		}
		if (n->getImplicitParamList()) {
			for (auto param: *n->getImplicitParamList()) {
				sbx symBx = visitChildNode(param,  shared_from_this());
				zDef->addParam(dynSp<ZParam>(symBx->getZSymbol()));
			}
		}
	}

	void ZVisitor::visit(sp<fClassParamClauses> n, sbx prnSbx) {
		ZVisitParamHelp::visitClassParamClauses(n, prnSbx, shared_from_this());
	}


	void ZVisitor::visit(sp<fTypeParamClause> n, sbx prnSbx) {
		ZVisitTypeParamHelp::visitTypeParamClause(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fVariantTypeParam> n, sbx prnSbx) {
		ZVisitTypeParamHelp::visitVariantTypeParam(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fParam> n, sbx prnSbx) {
		ZVisitParamHelp::visitParam(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassParam> n, sbx prnSbx) {
		ZVisitParamHelp::visitClassParam(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fParamType> n, sbx prnSbx) {
		n->getTypeTree()->accept(shared_from_this(), prnSbx);
	}

	void  ZVisitor::visit(sp<fType> n, sbx prnSbx)  {
		n->getTypeTree()->accept(shared_from_this(), prnSbx);
	}

	void ZVisitor::visit(sp<fClassParents> n, sbx prnSbx) {
		ZVisitClassHelp::visitClassParents(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassConstr> n, sbx prnSbx) {
		ZVisitClassHelp::visitClassConstr(n, prnSbx, shared_from_this());
	}


	void ZVisitor::visit(sp<fIf> n, sbx prnSbx) {
		std::cout << "-- IF Cond Expr" << std::endl;

		sp<ZIf> zDef = initScopeSymbol<ZIf>(prnSbx);

		sbx symBx = visitChildNode(n->getCondExpr(),  shared_from_this());
		zDef->setCondExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());

		if (n->getIfBody()) {
			symBx = visitChildNode(n->getIfBody(), shared_from_this());
			zDef->setBody(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getElseBody()) {
			symBx = visitChildNode(n->getElseBody(),  shared_from_this());
			zDef->setElseBody(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fValueDcl> n, sbx prnSbx) {
		std::cout << "Visiting Value Decl: " << std::endl;

		sp<ZValueDcl> zDef = initScopeSymbol<ZValueDcl>(prnSbx);

		if (n->getModifiers()) {
			sbx symBx = visitChildNode(n->getModifiers(), shared_from_this());
			zDef->setModifiers(dynSp<ZModifiers>(symBx->getZSymbol()));
		}

		for (const auto& name : n->getNames()) {
			sbx symBx = visitChildNode(name,  shared_from_this());
			zDef->addName(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getType()) {
			sbx symBx = visitChildNode(n->getType(),  shared_from_this());
			zDef->setType(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getAssignExpr()) {
			sbx symBx = visitChildNode(n->getAssignExpr(), shared_from_this());
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fWhile > n, sbx prnSbx) {
		std::cout << "-- WHILE Cond Expr" << std::endl;

		sp<ZWhile> zDef = initScopeSymbol<ZWhile>(prnSbx);

		sbx symBx = visitChildNode(n->getCondExpr(), shared_from_this());
		zDef->setCondExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		if (n->getBody()) {
			symBx = visitChildNode(n->getBody(),  shared_from_this());
			zDef->setBody(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fCaseClause> n, sbx prnSbx) {
		std::cout << "Visiting Case Clause" << std::endl;

		sp<ZCaseClause> zDef = initScopeSymbol<ZCaseClause>(prnSbx);

		if (n->getPattern()) {
			std::cout << "Visiting Case Clause Pattern" << std::endl;
			sbx symBx = visitChildNode(n->getPattern(), shared_from_this());
			zDef->setPattern(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getGuard()) {
			std::cout << "Visiting Case Clause Guard" << std::endl;
			sbx symBx = visitChildNode(n->getGuard(), shared_from_this());
			zDef->setGuard(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getBlock()) {
			std::cout << "Visiting Case Clause Block" << std::endl;
			sbx symBx = visitChildNode(n->getBlock(), shared_from_this());
			zDef->setBlock(dynSp<ZBlock>(symBx->getZSymbol()));
		}
	}

	void ZVisitor::visit(sp<fFor> n, sbx prnSbx) {
		std::cout << "Visiting For Loop" << std::endl;

		sp<ZFor> zDef = initScopeSymbol<ZFor>(prnSbx);

		for (const auto& gen : n->getGenerators()) {
			sbx symBx = visitChildNode(gen, shared_from_this());
			zDef->addGenerator(dynSp<ZGenerator>(symBx->getZSymbol()));
		}

		if (n->getYieldExpr()) {
			sbx symBx = visitChildNode(n->getYieldExpr(), shared_from_this());
			zDef->setYieldExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fGenerator> n, sbx prnSbx) {
		std::cout << "Visiting Generator" << std::endl;
		sp<ZGenerator> zDef = initScopeSymbol<ZGenerator>(prnSbx);

		if (n->getCasePattern1()) {
			sbx symBx = visitChildNode(n->getCasePattern1(), shared_from_this());
			zDef->setCasePattern1(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		for (const auto& guard : n->getGuards()) {
			sbx symBx = visitChildNode(guard, shared_from_this());
			zDef->addGuard(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		for (const auto& ep : n->getEndingPattern1s()) {
			sbx symBx = visitChildNode(ep, shared_from_this());
			zDef->addEndingPattern1(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}

		for (const auto& ee : n->getEndingExprs()) {
			sbx symBx = visitChildNode(ee, shared_from_this());
			zDef->addEndingExpr(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fCaseClauses> n, sbx prnSbx) {
		std::cout << "Visiting Case Clauses" << std::endl;
		sp<ZCaseClauses> zDef = initScopeSymbol<ZCaseClauses>(prnSbx);
		for (const auto& caseClause : n->getCaseClauses()) {
			sbx symBx = visitChildNode(caseClause, shared_from_this());
			zDef->addCaseClause(dynSp<ZCaseClause>(symBx->getZSymbol()));
		}
	}



	void ZVisitor::visit(sp<fConstrBlock> n, sbx prnSbx) {
		std::cout << "Visiting Constructor Block" << std::endl;
		sp<ZConstrBlock> zDef = initScopeSymbol<ZConstrBlock>(prnSbx);

		if (n->getArgExprs()) {
			std::cout << "Visiting Constructor Block Argument Expressions" << std::endl;
			for (const auto& argExpr : *n->getArgExprs()) {
				sbx symBx = visitChildNode(argExpr, shared_from_this());
				zDef->addArgExprs(dynSp<ZProdSubTreeN>(symBx->getZSymbol())->getTreePostOrderSS());
			}
		}

		if (n->getBlockStmts()) {
			std::cout << "Visiting Constructor Block Statements" << std::endl;
			for (const auto& stmt : *n->getBlockStmts()) {
				sp<ast::fLangOprnd> langOprnd = std::dynamic_pointer_cast<ast::fLangOprnd>(stmt);
				sbx symBx = visitChildNode(langOprnd, shared_from_this());
				zDef->addStmt(dynSp<ZSymbol>(symBx->getZSymbol()));
			}
		}
	}



	void ZVisitor::visit(sp<fFunc> n, sbx prnSbx) {
		std::cout << "Visiting fFun" << std::endl;
		throw std::runtime_error("Unimplemented");
	}



	void ZVisitor::visit(sp<fId> n, sbx prnSbx) {
		std::cout << "Visiting Identifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fIds> n, sbx prnSbx) {
		std::cout << "Visiting Identifiers" << std::endl;
		// for (const auto& id : n->getIds()) {
		// 	id->accept(shared_from_this(), prnSbx);
		// }
	}


	void ZVisitor::visit(sp<fLocalModifier> n, sbx prnSbx) {
		std::cout << "Visiting Local Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fModifier> n, sbx prnSbx) {
		std::cout << "Visiting Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fModifiers> n, sbx prnSbx) {
		std::cout << "Visiting Modifiers" << std::endl;

		sp<ZModifiers> zDef = initScopeSymbol<ZModifiers>(prnSbx);
		if (n->getAccessModifier()) {
			// std::cout << "Visiting Access Modifier in Modifiers" << std::endl;
			// n->getAccessModifier()->accept(shared_from_this(), prnSbx);
			sbx subSc = visitChildNode(n->getAccessModifier(), shared_from_this());
			zDef->addModifiers("access");
		}

		// if (n->getOverrideModifier()) {
		// 	std::cout << "Visiting Override Modifier in Modifiers" << std::endl;
		// 	n->getOverrideModifier()->accept(shared_from_this(), prnSbx);
		// }
		// if (n->getLocalModifiers()) {
		// 	std::cout << "Visiting Local Modifier in Modifiers" << std::endl;
		// 	for (auto m : *(n->getLocalModifiers())) {
		// 		m->accept(shared_from_this(), prnSbx);
		// 	}
		// }
	}

	void ZVisitor::visit(sp<fRegFunc> fun, sbx prnSbx) {
		ZVisitFuncHelp::visitRegFunc(fun, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fFunTypeParamClause> n, sbx prnSbx) {
		ZVisitTypeParamHelp::visitFunTypeParamClause(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fOverrideModifier> n, sbx prnSbx) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fParamTypes> n, sbx prnSbx) {
		ZVisitParamHelp::visitParamTypes(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fFunSig> n, sbx prnSbx) {
		ZVisitFuncHelp::visitFunSig(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fReturn> n, sbx prnSbx) {
		std::cout << "Visiting Return Statement" << std::endl;
		// if (n->getReturnExpr()) {
		// 	n->getReturnExpr()->accept(shared_from_this(), prnSbx);
		// }
	}

	void ZVisitor::visit(sp<fThisFunc> n, sbx prnSbx) {
		ZVisitFuncHelp::visitThisFunc(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fThrow> n, sbx prnSbx) {
		std::cout << "Visiting Throw" << std::endl;
		// if (n->getThrowExpr()) {
		// 	n->getThrowExpr()->accept(shared_from_this(), prnSbx);
		// }
	}

	void ZVisitor::visit(sp<fTraitDef> n, sbx prnSbx) {
		ZVisitClassHelp::visitTraitDef(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fTry> n, sbx prnSbx) {
		std::cout << "Visiting Try Block" << std::endl;
		// if (n->getTryBlock()) {
		// 	std::cout << "Visiting Try Block Body" << std::endl;
		// 	n->getTryBlock()->accept(shared_from_this(), prnSbx);
		// }
		// if (n->getCatchBlock()) {
		// 	std::cout << "Visiting Catch Clauses in Try Block" << std::endl;
		// 	n->getCatchBlock()->accept(shared_from_this(), prnSbx);
		// }
	}

	void ZVisitor::visit(sp<fTypeArgs> n, sbx prnSbx) {
		std::cout << "Visiting Type Arguments" << std::endl;

		sp<ZTypeList> zDef = initScopeSymbol<ZTypeList>(prnSbx);

		for (const auto& typeArg : n->getTypeArgs()) {
			sbx subSc = visitChildNode(typeArg, shared_from_this());
			zDef->addType(dynSp<ZType>(subSc->getZSymbol()));
		}
	}
	void ZVisitor::visit(sp<fTypeDef> n, sbx prnSbx) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
		// if (n->getTypeParams()) {
		// 	n->getTypeParams()->accept(shared_from_this(), prnSbx);
		// }
		// if (n->getAssignedType()) {
		// 	n->getAssignedType()->accept(shared_from_this(), prnSbx);
		// }
	}

	void ZVisitor::visit(sp<fTypeParam> n, sbx prnSbx) {
		ZVisitTypeParamHelp::visitTypeParam(n, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fUnderscore> n, sbx prnSbx) {
		std::cout << "Visiting Underscore: " <<n ->toString() << std::endl;
	}



	sp<fAstNod> ZVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree) {
		return ZVisitPSubTreeHelp::getAstPSTreeRightN(subTree);
	}

	void ZVisitor::visit(sp<fAstProdSubTreeN> subTr, sbx prnSbx) {
		ZVisitPSubTreeHelp::traverseProdSubTree(subTr, prnSbx, shared_from_this());
	}

	void ZVisitor::visit(sp<fVarargsExpansion> n, sbx prnSbx) {
		std::cout << "Visiting Varargs Expansion: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fAccessModifier> n, sbx prnSbx) {
		std::cout << "Visiting Access Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fAccessQualifier> n, sbx prnSbx) {
		std::cout << "Visiting Access Qualifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fBlock> n, sbx prnSbx) {
		ZVisitClassHelp::visitBlock(n, prnSbx, shared_from_this());
	}

	void  ZVisitor::visit(sp<fAstOprndNod> n, sbx prnSbx)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fAstOptrNod> n, sbx prnSbx)  {
		std::cout << "Operator: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSbx);
	}

	void  ZVisitor::visit(sp<fLiteral> n, sbx prnSbx)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSbx);
	}

	void  ZVisitor::visit(sp<fStableId>n, sbx prnSbx)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSbx);
	}


	void ZVisitor::visit(sp<fPackage> n, sbx prnSbx) {}

	void ZVisitor::visit(sp<fImport> n, sbx prnSbx) {

		sp<ZImport> zDef = initScopeSymbol<ZImport>(prnSbx);

		for (sp<fImportExpr>& impExpr : n->getImportExprs()) {
			std::string qualName = impExpr->getId()->getQualName();
			if (impExpr->getUnderscore()) {
				qualName += "._";
				zDef->addImport(std::move(qualName));

			} else if (impExpr->getSelectors()) {

				for (size_t i = 0; i < impExpr->getSelectors()->size(); i++) {
					std::string qualNameSel =  qualName + "." + impExpr->getSelectors()->at(i)->getFrom()->toString();
					// zim->addImport(std::move(qualNameSel));
					zDef->addImport(std::move(qualNameSel));
				}
			} else {
				// zim->addImport(std::move(qualName));
				zDef->addImport(std::move(qualName));
			}
		}

		// sp<ZStmtList> ss = std::dynamic_pointer_cast<ZStmtList>(prnSbx->getZSymbol());
		// zaccert(ss != nullptr, "Expected ZStatementList in scope for import statement");
		// ss->addStmt(zim);
	}
}
