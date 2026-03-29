
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

	// void ZVisitor::visit() {
	// 	std::cout << "--- Visitor starts ---" << std::endl;
	// 	sp<ZEnclScope> programSc = ms<ZEnclScope>(nullptr);
	// 	sp<ZProgram> zDef = initScopeSymbol<ZProgram>(programSc);
	// 	esc subSc = visitChildNode(ms<fCompileUnit>(),  programSc, shared_from_this());
	// 	zDef->addCompileUnit(dynSp<ZCompileUnit>(subSc->getZSymbol()));
	// }


	void ZVisitor::visit() {
		// std::cout << "--- Visitor starts ---" << std::endl;
		sp<ZSymbolBox> programSc = ms<ZSymbolBox>();
		// sp<ZProgram> zDef = initScopeSymbol<ZProgram>(programSc);
		compileUnit_->accept(shared_from_this(), programSc);
	}


	void ZVisitor::visit(sp<fCompileUnit> n, sbx prnSc)  {

		sp<ZCompileUnit> zDef = ms<ZCompileUnit>("ZCompileUnit");

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
				sbx subSc = visitChildNode(langOprnd,  shared_from_this());
				zDef->addStmt(dynSp<ZSymbol>(subSc->getZSymbol()));
			}
		}
	}

	void  ZVisitor::visit(sp<fClassDef> cls, sbx prnSc){
		ZVisitClassHelp::visitClassDef(cls, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fObjectDef> obj, sbx prnSc) {
		ZVisitClassHelp::visitObjectDef(obj, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassTemplate> n, sbx prnSc) {
		ZVisitClassHelp::visitClassTemplate(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplate> n, sbx prnSc) {
		ZVisitClassHelp::visitTemplate(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplateBody> n, sbx prnSc) {
		ZVisitClassHelp::visitTemplateBody(n, prnSc, shared_from_this());
	}


	void ZVisitor::visit(sp<fParamClauses> n, sbx prnSc) {

		sp<ZParamList> zDef = initScopeSymbol<ZParamList>(prnSc);

		for (auto paramList : n->getParamLists()) {
			for (auto param : paramList) {
				sbx subSc = visitChildNode(param, shared_from_this());
				zDef->addParam(dynSp<ZParam>(subSc->getZSymbol()));
			}
		}
		if (n->getImplicitParamList()) {
			for (auto param: *n->getImplicitParamList()) {
				sbx subSc = visitChildNode(param,  shared_from_this());
				zDef->addParam(dynSp<ZParam>(subSc->getZSymbol()));
			}
		}
	}

	void ZVisitor::visit(sp<fClassParamClauses> n, sbx prnSc) {
		ZVisitParamHelp::visitClassParamClauses(n, prnSc, shared_from_this());
	}


	void ZVisitor::visit(sp<fTypeParamClause> n, sbx prnSc) {
		ZVisitTypeParamHelp::visitTypeParamClause(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fVariantTypeParam> n, sbx prnSc) {
		ZVisitTypeParamHelp::visitVariantTypeParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fParam> n, sbx prnSc) {
		ZVisitParamHelp::visitParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassParam> n, sbx prnSc) {
		ZVisitParamHelp::visitClassParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fParamType> n, sbx prnSc) {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void  ZVisitor::visit(sp<fType> n, sbx prnSc)  {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void ZVisitor::visit(sp<fClassParents> n, sbx prnSc) {
		ZVisitClassHelp::visitClassParents(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassConstr> n, sbx prnSc) {
		ZVisitClassHelp::visitClassConstr(n, prnSc, shared_from_this());
	}


	void ZVisitor::visit(sp<fIf> n, sbx prnSc) {
		std::cout << "-- IF Cond Expr" << std::endl;

		sp<ZIf> zDef = initScopeSymbol<ZIf>(prnSc);

		sbx subSc = visitChildNode(n->getCondExpr(),  shared_from_this());
		zDef->setCondExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());

		if (n->getIfBody()) {
			sbx subSc = visitChildNode(n->getIfBody(), shared_from_this());
			zDef->setBody(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getElseBody()) {
			sbx subSc = visitChildNode(n->getElseBody(),  shared_from_this());
			zDef->setElseBody(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fValueDcl> n, sbx prnSc) {
		std::cout << "Visiting Value Decl: " << std::endl;

		sp<ZValueDcl> zDef = initScopeSymbol<ZValueDcl>(prnSc);

		if (n->getModifiers()) {
			sbx subSc = visitChildNode(n->getModifiers(), shared_from_this());
			zDef->setModifiers(dynSp<ZModifiers>(subSc->getZSymbol()));
		}

		for (const auto& name : n->getNames()) {
			// val->addName(ZVisitPSubTreeHelp::visitIntoSubTree(name, prnSc, shared_from_this()));
			sbx subSc = visitChildNode(name,  shared_from_this());
			zDef->addName(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getType()) {
			sbx subSc = visitChildNode(n->getType(),  shared_from_this());
			zDef->setType(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}

		if (n->getAssignExpr()) {
			sbx subSc = visitChildNode(n->getAssignExpr(), shared_from_this());
			zDef->setDefaultValueExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fWhile > n, sbx prnSc) {
		std::cout << "-- WHILE Cond Expr" << std::endl;

		sp<ZWhile> zDef = initScopeSymbol<ZWhile>(prnSc);

		sbx subSc = visitChildNode(n->getCondExpr(), shared_from_this());
		zDef->setCondExpr(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		if (n->getBody()) {
			sbx subSc = visitChildNode(n->getBody(),  shared_from_this());
			zDef->setBody(dynSp<ZProdSubTreeN>(subSc->getZSymbol())->getTreePostOrderSS());
		}
	}

	void ZVisitor::visit(sp<fAccessModifier> n, sbx prnSc) {
		std::cout << "Visiting Access Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fAccessQualifier> n, sbx prnSc) {
		std::cout << "Visiting Access Qualifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fBlock> n, sbx prnSc) {
		ZVisitClassHelp::visitBlock(n, prnSc, shared_from_this());
	}
	void ZVisitor::visit(sp<fCaseClause> n, sbx prnSc) {
		// std::cout << "Visiting Case Clause" << std::endl;
		// if (n->getPattern()) {
		// 	std::cout << "Visiting Case Clause Pattern" << std::endl;
		// 	n->getPattern()->accept(shared_from_this(), prnSc);
		// }
		// if (n->getGuard()) {
		// 	std::cout << "Visiting Case Clause Guard" << std::endl;
		// 	n->getGuard()->accept(shared_from_this(), prnSc);
		// }
		// if (n->getBlock()) {
		// 	std::cout << "Visiting Case Clause Block" << std::endl;
		// 	n->getBlock()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fCaseClauses> n, sbx prnSc) {
		std::cout << "Visiting Case Clauses" << std::endl;
		// for (const auto& caseClause : n->getCaseClauses()) {
		// 	caseClause->accept(shared_from_this(), prnSc);
		// }
	}



	void ZVisitor::visit(sp<fConstrBlock> n, sbx prnSc) {
		std::cout << "Visiting Constructor Block" << std::endl;
		// if (n->getArgExprs()) {
		// 	std::cout << "Visiting Constructor Block Argument Expressions" << std::endl;
		// 	ZVisitPSubTreeHelp::visitIntoSubTree(n->getArgExprs(), prnSc, shared_from_this());
		// }
		// if (n->getBlockStmts().size() > 0) {
		// 	std::cout << "Visiting Constructor Block Statements" << std::endl;
		// 	for (const auto& stmt : n->getBlockStmts()) {
		// 		stmt->accept(shared_from_this(), prnSc);
		// 	}
		// }
	}

	void ZVisitor::visit(sp<fFor> n, sbx prnSc) {
		std::cout << "Visiting For Loop" << std::endl;
		// if (n->getGenerators().size() > 0) {
		// 	std::cout << "Visiting Generators in For Loop" << std::endl;
		// 	for (const auto& gen : n->getGenerators()) {
		// 		gen->accept(shared_from_this(), prnSc);
		// 	}
		// }
		// if (n->getYieldExpr()) {
		// 	std::cout << "Visiting For Loop Body" << std::endl;
		// 	n->getYieldExpr()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fFunc> n, sbx prnSc) {
		std::cout << "Visiting fFun" << std::endl;
		throw std::runtime_error("Unimplemented");
	}

	void ZVisitor::visit(sp<fGenerator> n, sbx prnSc) {
		std::cout << "Visiting Generator" << std::endl;
		// if (n->getCasePattern1()) {
		// 	std::cout << "Visiting Enumerator in Generator" << std::endl;
		// 	n->getCasePattern1()->accept(shared_from_this(), prnSc);
		// }
		// for (const auto& guard : n->getGuards()) {
		// 	std::cout << "Visiting Guard in Generator" << std::endl;
		// 	guard->accept(shared_from_this(), prnSc);
		// }
		// for (const auto& ep : n->getEndingPattern1s()) {
		// 	std::cout << "Visiting Ending Pattern in Generator" << std::endl;
		// 	ep->accept(shared_from_this(), prnSc);
		// }
		// for (const auto& ee : n->getEndingExprs()) {
		// 	std::cout << "Visiting Ending Expression in Generator" << std::endl;
		// 	ee->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fId> n, sbx prnSc) {
		std::cout << "Visiting Identifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fIds> n, sbx prnSc) {
		std::cout << "Visiting Identifiers" << std::endl;
		// for (const auto& id : n->getIds()) {
		// 	id->accept(shared_from_this(), prnSc);
		// }
	}


	void ZVisitor::visit(sp<fLocalModifier> n, sbx prnSc) {
		std::cout << "Visiting Local Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fModifier> n, sbx prnSc) {
		std::cout << "Visiting Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fModifiers> n, sbx prnSc) {
		std::cout << "Visiting Modifiers" << std::endl;

		sp<ZModifiers> zDef = initScopeSymbol<ZModifiers>(prnSc);
		if (n->getAccessModifier()) {
			// std::cout << "Visiting Access Modifier in Modifiers" << std::endl;
			// n->getAccessModifier()->accept(shared_from_this(), prnSc);
			sbx subSc = visitChildNode(n->getAccessModifier(), shared_from_this());
			zDef->addModifiers("access");
		}

		// if (n->getOverrideModifier()) {
		// 	std::cout << "Visiting Override Modifier in Modifiers" << std::endl;
		// 	n->getOverrideModifier()->accept(shared_from_this(), prnSc);
		// }
		// if (n->getLocalModifiers()) {
		// 	std::cout << "Visiting Local Modifier in Modifiers" << std::endl;
		// 	for (auto m : *(n->getLocalModifiers())) {
		// 		m->accept(shared_from_this(), prnSc);
		// 	}
		// }
	}

	void ZVisitor::visit(sp<fRegFunc> fun, sbx prnSc) {
		ZVisitFuncHelp::visitRegFunc(fun, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fFunTypeParamClause> n, sbx prnSc) {
		ZVisitTypeParamHelp::visitFunTypeParamClause(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fOverrideModifier> n, sbx prnSc) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fParamTypes> n, sbx prnSc) {
		ZVisitParamHelp::visitParamTypes(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fFunSig> n, sbx prnSc) {
		ZVisitFuncHelp::visitFunSig(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fReturn> n, sbx prnSc) {
		std::cout << "Visiting Return Statement" << std::endl;
		// if (n->getReturnExpr()) {
		// 	n->getReturnExpr()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fThisFunc> n, sbx prnSc) {
		ZVisitFuncHelp::visitThisFunc(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fThrow> n, sbx prnSc) {
		std::cout << "Visiting Throw" << std::endl;
		// if (n->getThrowExpr()) {
		// 	n->getThrowExpr()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fTraitDef> n, sbx prnSc) {
		ZVisitClassHelp::visitTraitDef(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTry> n, sbx prnSc) {
		std::cout << "Visiting Try Block" << std::endl;
		// if (n->getTryBlock()) {
		// 	std::cout << "Visiting Try Block Body" << std::endl;
		// 	n->getTryBlock()->accept(shared_from_this(), prnSc);
		// }
		// if (n->getCatchBlock()) {
		// 	std::cout << "Visiting Catch Clauses in Try Block" << std::endl;
		// 	n->getCatchBlock()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fTypeArgs> n, sbx prnSc) {
		std::cout << "Visiting Type Arguments" << std::endl;

		sp<ZTypeList> zDef = initScopeSymbol<ZTypeList>(prnSc);

		for (const auto& typeArg : n->getTypeArgs()) {
			sbx subSc = visitChildNode(typeArg, shared_from_this());
			zDef->addType(dynSp<ZType>(subSc->getZSymbol()));
		}
	}
	void ZVisitor::visit(sp<fTypeDef> n, sbx prnSc) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
		// if (n->getTypeParams()) {
		// 	n->getTypeParams()->accept(shared_from_this(), prnSc);
		// }
		// if (n->getAssignedType()) {
		// 	n->getAssignedType()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fTypeParam> n, sbx prnSc) {
		ZVisitTypeParamHelp::visitTypeParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fUnderscore> n, sbx prnSc) {
		std::cout << "Visiting Underscore: " <<n ->toString() << std::endl;
	}



	sp<fAstNod> ZVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree) {
		return ZVisitPSubTreeHelp::getAstPSTreeRightN(subTree);
	}

	void ZVisitor::visit(sp<fAstProdSubTreeN> subTr, sbx prnSc) {
		ZVisitPSubTreeHelp::traverseProdSubTree(subTr, prnSc, shared_from_this());
	}


	void  ZVisitor::visit(sp<fAstOprndNod> n, sbx prnSc)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fAstOptrNod> n, sbx prnSc)  {
		std::cout << "Operator: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fLiteral> n, sbx prnSc)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fStableId>n, sbx prnSc)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
		// ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}


	void ZVisitor::visit(sp<fPackage> n, sbx prnSc) {}

	void ZVisitor::visit(sp<fImport> n, sbx prnSc) {

		sp<ZImport> zDef = initScopeSymbol<ZImport>(prnSc);

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

		// sp<ZStmtList> ss = std::dynamic_pointer_cast<ZStmtList>(prnSc->getZSymbol());
		// zaccert(ss != nullptr, "Expected ZStatementList in scope for import statement");
		// ss->addStmt(zim);
	}
}
