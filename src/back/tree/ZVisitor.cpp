
#include "back/tree/ZVisitor.hpp"

#include <iostream>
#include <stack>

#include "ast/leaf/fAccessQualifier.hpp"
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
#include "ast/leaf/fNamedFun.hpp"
#include "ast/leaf/fObject.hpp"
#include "ast/leaf/fOverrideModifier.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/leaf/fReturn.hpp"
#include "ast/leaf/fTemplateBody.hpp"
#include "ast/leaf/fThisFun.hpp"
#include "ast/leaf/fThrow.hpp"
#include "ast/leaf/fTry.hpp"
#include "ast/leaf/fTypeDef.hpp"
#include "ast/leaf/fTypeParam.hpp"
#include "ast/leaf/fUnderscore.hpp"
#include "ast/leaf/fValueDecl.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"

namespace zebra::back::tree {



	void ZVisitor::visit() {
		std::cout << "Visitor starts" << std::endl;
		esc s = ms<ZEnclScope>(nullptr, fLangGrmrProdE::COMPILATION_UNIT);
		compileUnit_->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fCompileUnit> n, esc prnSc)  {
		std::cout << "Visiting Compile Unit" << std::endl;
		if (n->getPackages().size() > 0) {
			std::cout << "Visiting Packages in Compile Unit" << std::endl;
			for (const auto& pkg : n->getPackages()) {
				pkg->accept(shared_from_this(), prnSc);
			}
		}
		if (n->getImports().size() > 0) {
			std::cout << "Visiting Imports in Compile Unit" << std::endl;
			for (const auto& imp : n->getImports()) {
				imp->accept(shared_from_this(), prnSc);
			}
		}
		if (n->getStmts().size() > 0) {
			std::cout << "Visiting Statements in Compile Unit" << std::endl;
			for (const auto& stmt : n->getStmts()) {
				stmt->accept(shared_from_this(), prnSc);
			}
		}
	}

	void  ZVisitor::visit(sp<fClassDef> cls, esc prnSc){
		std::cout << "Visiting Class Definition: " << cls->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_TEMPLATE);
		s->addSymbol(cls->getName()->toString(), ms<ZClass>());

		if (cls->getModifiers()) {
			cls->getModifiers()->accept(shared_from_this(), prnSc);
		}

		if (cls->getConstrAccessModifier()) {
			cls->getConstrAccessModifier()->accept(shared_from_this(), s);
		}

		if (cls->getTypeParamClause()) {
			cls->getTypeParamClause()->accept(shared_from_this(), s);
		}

		if (cls->getClassParamClauses()) {
			cls->getClassParamClauses()->accept(shared_from_this(), s);
		}

		if (cls->getExtendsTemplate()) {
			std::cout << "Visiting extends template of class definition" << std::endl;
			cls->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void  ZVisitor::visit(sp<fLiteral> n, esc prnSc)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fStableId>n, esc prnSc)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fType> n, esc prnSc)  {
		std::cout << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fValueDef> n, esc prnSc)  {
		std::cout << "Visiting Value Decl: " << n->toString() << std::endl;
		assert(n->getNames().size() > 0);

		std::vector<sp<ZEnclScope>> esVec;// = ms<std::vector<EnclosingScope>>(prnSc, fLangGrmrProdE::VALUE_DEF);

		for (size_t i = 0; i < n->getNames().size(); i++) {
			std::cout << "Visiting name " << i << " of value declaration" << std::endl;

			esVec.push_back(ms<ZEnclScope>(prnSc, fLangGrmrProdE::VALUE_DEF));
			n->getNames()[i]->accept(shared_from_this(), esVec[i]);

			//prnSc->getPolishSS();
		}

		if (n->getType()) {
			n->getType()->accept(shared_from_this(), prnSc);
		}

		if (n->getModifiers()) {
			n->getModifiers()->accept(shared_from_this(), prnSc);
		}

		sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value declaration" << std::endl;
			assignExpr->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fIf> n, esc prnSc) {
		std::cout << "-- IF Cond Expr" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::IF);

		n->getCondExpr()->accept(shared_from_this(), s);
		std::cout << "-- IF Body Exp" << std::endl;
		n->getIfBody()->accept(shared_from_this(), s);
		if (n->getElseBody()) {
			std::cout << "-- IF_ELSE Body Exp" << std::endl;
			n->getElseBody()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fWhile > n, esc prnSc) {
		std::cout << "-- WHILE Cond Expr" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::WHILE);

		n->getCondExpr()->accept(shared_from_this(), s);
		std::cout << "-- WHILE Body Exp" << std::endl;
		n->getBody()->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fAccessModifier> n, esc prnSc) {
		std::cout << "Visiting Access Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fAccessQualifier> n, esc prnSc) {
		std::cout << "Visiting Access Qualifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fBlock> n, esc prnSc) {
		std::cout << "Visiting Block" << std::endl;
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(shared_from_this(), prnSc);
		}
	}
	void ZVisitor::visit(sp<fCaseClause> n, esc prnSc) {
		std::cout << "Visiting Case Clause" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CASE_CLAUSE);

		n->getPattern()->accept(shared_from_this(), s);
		if (n->getGuard()) {
			std::cout << "Visiting Case Guard" << std::endl;
			n->getGuard()->accept(shared_from_this(), s);
		}
		std::cout << "Visiting Case Body" << std::endl;
		n->getBlock()->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fCaseClauses> n, esc prnSc) {
		std::cout << "Visiting Case Clauses" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CASE_CLAUSES);
		for (const auto& clause : n->getCaseClauses()) {
			clause->accept(shared_from_this(), prnSc);
		}
	}
	void ZVisitor::visit(sp<fClassConstr> n, esc prnSc) {
		std::cout << "Visiting Class Constructor" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_CONSTR);
		n->getPrimaryCtorParamType()->accept(shared_from_this(), s);
		if (n->getArgs()) {
			std::cout << "Visiting Class Constructor Arguments" << std::endl;
			n->getArgs()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fClassParam> n, esc prnSc) {
		std::cout << "Visiting Class Parameter: " << n->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_PARAM);
		n->getParamType()->accept(shared_from_this(), s);

		sp<fAstProdSubTreeN> assignExpr = n->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for class parameter" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fClassParamClauses> n, esc prnSc) {
		std::cout << "Visiting Class Parameter Clauses" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_PARAM_CLAUSES);
		for (const auto& implicitParam : n->getImplicitParams()) {
			std::cout << "Visiting Implicit Class Parameter" << std::endl;
			implicitParam->accept(shared_from_this(), s);
		}
		for (const auto& paramClauseList : n->getClassParams()) {
			for (auto & paramClause : paramClauseList) {
				std::cout << "Visiting Class Parameter Clause" << std::endl;
				paramClause->accept(shared_from_this(), s);
			}
		}
	}

	void ZVisitor::visit(sp<fClassParents> n, esc prnSc) {
		std::cout << "Visiting Class Parents" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_PARENTS);
		if (n->getConstr()) {
			n->getConstr()->accept(shared_from_this(), s);
		}
		if (n->getWithTypes()) {
			n->getWithTypes()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fClassTemplate> n, esc prnSc) {
		std::cout << "Visiting Class Template" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CLASS_TEMPLATE);
		if (n->getClassParents()) {
			n->getClassParents()->accept(shared_from_this(), s);
		}
		if (n->getTemplateBody()) {
			n->getTemplateBody()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fConstrBlock> n, esc prnSc) {
		std::cout << "Visiting Constructor Block" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::CONSTR_BLOCK);
		if (n->getArgExprs()) {
			std::cout << "Visiting Constructor Block Argument Expressions" << std::endl;
			n->getArgExprs()->accept(shared_from_this(), s);
		}
		std::cout << "Visiting Constructor Block Statements" << std::endl;
		for (const auto& stmt : n->getBlockStmts()) {
			stmt->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fFor> n, esc prnSc) {
		std::cout << "Visiting For Loop" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::FOR);
		for (auto gen: n->getGenerators()) {
			gen->accept(shared_from_this(), s);
		}

		if (n->getYieldExpr()) {
			std::cout << "Visiting For Loop Yield Expression" << std::endl;
			n->getYieldExpr()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fFun> n, esc prnSc) {
		std::cout << "Visiting fFun" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::FFUN);
		n->getModifiers()->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fFunSig> n, esc prnSc) {
		std::cout << "Visiting Function Signature: " << n->getFunName()->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::FUN_SIG);
		if (n->getParamClauses()) {
			std::cout << "Visiting Function Parameter Clauses" << std::endl;
			n->getParamClauses()->accept(shared_from_this(), s);
		}
		if (n->getTypeParam()) {
			std::cout << "Visiting Function Type Parameters" << std::endl;
			auto typeParams = *n->getTypeParam().get();
			for (auto tpp : typeParams) {
					tpp->accept(shared_from_this(), prnSc);
			}
		}
	}

	void ZVisitor::visit(sp<fGenerator> n, esc prnSc) {
		std::cout << "Visiting Generator" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::GENERATOR);
		if (n->isCaseGenerator()) {
			std::cout << "Visiting Case Pattern" << std::endl;
			n->getCasePattern1()->accept(shared_from_this(), s);
		}
		for (const auto& guard : n->getGuards()) {
			std::cout << "Visiting Generator Guard" << std::endl;
			guard->accept(shared_from_this(), s);
		}
		if (n->getInExpr()) {
			std::cout << "Visiting Generator In Expression" << std::endl;
			n->getInExpr()->accept(shared_from_this(), s);
		}
		for (const auto& endingPattern : n->getEndingPattern1s()) {
			std::cout << "Visiting Generator Ending Pattern" << std::endl;
			endingPattern->accept(shared_from_this(), s);
		}
		for (const auto& endingExpr : n->getEndingExprs()) {
			std::cout << "Visiting Generator Ending Expression" << std::endl;
			endingExpr->accept(shared_from_this(), s);
		}
	}
	void ZVisitor::visit(sp<fId> n, esc prnSc) {
		std::cout << "Visiting Identifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fIds> n, esc prnSc) {
		std::cout << "Visiting Identifiers" << std::endl;
		for (const auto& id : n->getIds()) {
			id->accept(shared_from_this(), prnSc);
		}
	}
	// void fLangAstVisitor::visit(sp<fIf> n, esc prnSc) {}
	void ZVisitor::visit(sp<fImport> n, esc prnSc) {
		std::cout << "Visiting Import: " << n->toString() << std::endl;
	}
	// void fLangAstVisitor::visit(sp<fLiteral> n, esc prnSc) {}
	void ZVisitor::visit(sp<fLocalModifier> n, esc prnSc) {
		std::cout << "Visiting Local Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fModifier> n, esc prnSc) {
		std::cout << "Visiting Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fModifiers> n, esc prnSc) {
		std::cout << "Visiting Modifiers" << std::endl;
		if (n->getAccessModifier()) {
			std::cout << "Visiting Access Modifier in Modifiers" << std::endl;
			n->getAccessModifier()->accept(shared_from_this(), prnSc);
		}
		if (n->getOverrideModifier()) {
			std::cout << "Visiting Override Modifier in Modifiers" << std::endl;
			n->getOverrideModifier()->accept(shared_from_this(), prnSc);
		}
		if (n->getLocalModifiers()) {
			std::cout << "Visiting Local Modifier in Modifiers" << std::endl;
			for (auto m : *(n->getLocalModifiers())) {
				m->accept(shared_from_this(), prnSc);
			}
		}
	}
	void ZVisitor::visit(sp<fNamedFun> n, esc prnSc) {
		std::cout << "Visiting Named Function: " << n->getFunSig()->getFunName()->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::NAMED_FUN);
		if (n->getModifiers()) {
			n->getModifiers()->accept(shared_from_this(), s);
		}
		if (n->getFunSig()) {
			n->getFunSig()->accept(shared_from_this(), s);
		}
		std::cout << "Visiting Named Function Body" << std::endl;
		if (n->getFunBody()) {
			n->getFunBody()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fObject> n, esc prnSc) {
		if (n->isCaseClass()) {
			std::cout << "Visiting Case Class: " << n->getObjectName()->toString()  << std::endl;
		} else {
			std::cout << "Visiting Class: " << n->getObjectName()->toString() << std::endl;
		}
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::OBJECT);
		if (n->getModifiers()) {
			n->getModifiers()->accept(shared_from_this(), s);
		}
		if (n->getExtendsTemplate()) {
			n->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fOverrideModifier> n, esc prnSc) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fPackage> n, esc prnSc) {
		std::cout << "Visiting Package: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fParam> n, esc prnSc) {
		std::cout << "Visiting Parameter: " << n->getIdentifier()->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::PARAM);
		 sp<fAstProdSubTreeN> assignExpr = n->getDefaultValue();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for parameter" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}
	void ZVisitor::visit(sp<fParamClauses> n, esc prnSc) {
		std::cout << "Visiting Parameter Clauses" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::PARAM_CLAUSES);
		for (auto paramV : n->getParams()) {
			for (auto param : paramV) {
				std::cout << "Visiting Parameter Clause" << std::endl;
				param->accept(shared_from_this(), s);
			}
		}
	}

	void ZVisitor::visit(sp<fParamType> n, esc prnSc) {
		std::cout << "Visiting Parameter Type" << std::endl;
		if (n->getType()) {
			n->getType()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fParamTypes> n, esc prnSc) {
		std::cout << "Visiting Parameter Types" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::PARAM_TYPES);
		if (n->getParamTypes()) {
			for (auto ptp : *n->getParamTypes().get()) {
				ptp->accept(shared_from_this(), s);
			}
		}
	}

	void ZVisitor::visit(sp<fReturn> n, esc prnSc) {
		std::cout << "Visiting Return Statement" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::RETURN);
		if (n->getReturnExpr()) {
			std::cout << "Visiting Return Expression" << std::endl;
			n->getReturnExpr()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fTemplate> n, esc prnSc) {
		std::cout << "Visiting Template" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TEMPLATE);
		if (n->getTemplateBody()) {
			std::cout << "Visiting Template Body of Template" << std::endl;
			 n->getTemplateBody()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fTemplateBody> n, esc prnSc) {
		std::cout << "Visiting Template Body" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TEMPLATE_BODY);
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(shared_from_this(), s);
		}
	}
	void ZVisitor::visit(sp<fThisFun> n, esc prnSc) {
		std::cout << "Visiting This Function" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::THIS_FUN);
		if (n->getParamClauses()) {
			std::cout << "Visiting Parameter Clauses of This Function" << std::endl;
			n->getParamClauses()->accept(shared_from_this(), s);
		}
		if (n->getConstrBlock()) {
			std::cout << "Visiting Constructor Block of This Function" << std::endl;
			n->getConstrBlock()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fThrow> n, esc prnSc) {
		std::cout << "Visiting Throw" << std::endl;
		if (n->getThrowExpr()) {
			n->getThrowExpr()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTraitDef> n, esc prnSc) {
		std::cout << "Visiting Trait Definition: " << n->getName()->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TRAIT_DEF);
		if (n->getExtendsTemplate()) {
			std::cout << "Visiting extends template of trait definition" << std::endl;
			n->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fTry> n, esc prnSc) {
		std::cout << "Visiting Try Block" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TRY);
		n->getTryBlock()->accept(shared_from_this(), s);
		// for (const auto& catchClause : n->getCatchClauses()) {
		// 	std::cout << "Visiting Catch Clause" << std::endl;
		// 	catchClause->accept(shared_from_this(), prnSc);
		// }
		if (n->getFinallyBlock()) {
			std::cout << "Visiting Finally Block" << std::endl;
			n->getFinallyBlock()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fTypeArgs> n, esc prnSc) {
		std::cout << "Visiting Type Arguments" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TYPE_ARGS);
		for (const auto& typeArg : n->getTypeArgs()) {
			typeArg->accept(shared_from_this(), s);
		}
	}
	void ZVisitor::visit(sp<fTypeDef> n, esc prnSc) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TYPE_DEF);
		if (n->getAssignedType()) {
			std::cout << "Visiting Assigned Type of Type Definition" << std::endl;
			 n->getAssignedType()->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fTypeParam> n, esc prnSc) {
		std::cout << "Visiting Type Parameter: " << n->getTypeParamName()->toString() << std::endl;
		// if (n->getTypeBound()) {
		// 	std::cout << "Visiting Type Bound for Type Parameter" << std::endl;
		// 	n->getTypeBound()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fUnderscore> n, esc prnSc) {
		std::cout << "Visiting Underscore: " <<n ->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fValue> n, esc prnSc) {
		// std::cout << "Visiting Value: " << n->getName()->toString() << std::endl;
		 sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value" << std::endl;
			assignExpr->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fValueDecl> n, esc prnSc) {
		std::cout << "Visiting Value Declaration: " << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::VALUE_DECL);
		for (auto name: n->getNames()) {
			std::cout << "Visiting name of value declaration" << std::endl;
			name->accept(shared_from_this(), s);
		}

		if (n->getType()) {
			std::cout << "Visiting Type of Value Declaration" << std::endl;
			n->getType()->accept(shared_from_this(), prnSc);
		}

		 sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value declaration" << std::endl;
			assignExpr->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTypeParamClause> n, esc prnSc) {
		std::cout << "Visiting Type Parameter Clause" << std::endl;
		esc s = ms<ZEnclScope>(prnSc, fLangGrmrProdE::TYPE_PARAM_CLAUSE);
		for (auto typeParam : *n->getVariantTypeParams()) {
			typeParam->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fVariantTypeParam> n, esc prnSc) {
		std::cout << "Visiting Variant Type Parameter: " << n->toString() << std::endl;
		prnSc->addSymbol(n->getTypeParamName()->toString(), ms<ZVariantTypeParam>(n));
	}


	sp<fAstNod> ZVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTr) {
		while (true) {
			sp<fAstNod> subTRight = subTr->getRootOpNod()->getAstRightN();
			sp<fAstProdSubTreeN> subTRight_SubTr =std::dynamic_pointer_cast<fAstProdSubTreeN>(subTRight);
			if (!subTRight_SubTr) {
				return subTRight;
			}
			subTr = subTRight_SubTr;
		}
	}

	class fAstStackItem {
		sp<fAstNod> node;
		bool leftVisited, rightVisited;
	public:
		fAstStackItem(sp<fAstNod> node) : node(node), leftVisited(false), rightVisited(false) {
			if (this->node == nullptr) {
				throw std::invalid_argument("AST node in stack item cannot be null");
			}
		}
		void setLeftVisited() { leftVisited = true; }
		void setRightVisited() { rightVisited = true; }
		bool isLeftVisited() const { return leftVisited; }
		bool isRightVisited() const { return rightVisited; }
		sp<fAstNod> getNode() const { return node; }
	};



	void ZVisitor::visit(sp<fAstProdSubTreeN> subTr,  esc prnSc) {


		std::cout << subTr->toString() << std::endl;
		std::stack<sp<fAstStackItem>> ss;
		sp<fAstNod> psubT = getAstPSTreeRightN(subTr);
		if (!psubT) {
			return;
		}

		sp<std::vector<sp<fAstNod>>> polishCalcSS = ms<std::vector<sp<fAstNod>>>();
		ss.push(ms<fAstStackItem>(psubT));

		while (!ss.empty()) {
			sp<fAstStackItem> currItem = ss.top();
			sp<fAstNod> currNode = currItem->getNode();
			if (currNode == nullptr) {
				throw std::runtime_error("Current node in AST stack cannot be null");
			}
			if (!currItem->isLeftVisited()) {
				currItem->setLeftVisited();
				if (currNode->getAstLeftN()) {
					sp<fAstProdSubTreeN> leftSubTr =std::dynamic_pointer_cast<fAstProdSubTreeN>( currNode->getAstLeftN());
					if (leftSubTr) {
						sp<fAstNod> pst = getAstPSTreeRightN(leftSubTr);
						if (pst) {
							ss.push(ms<fAstStackItem>(pst));
						}

					} else {
						ss.push(ms<fAstStackItem>(currNode->getAstLeftN()));
					}
					continue;
				}
			}

			if (!currItem->isRightVisited() ) {
				currItem->setRightVisited();
				if (currNode->getAstRightN()) {
					sp<fAstProdSubTreeN> rightSubTr =std::dynamic_pointer_cast<fAstProdSubTreeN>( currNode->getAstRightN());
					if (rightSubTr) {
						sp<fAstNod> pst = getAstPSTreeRightN(rightSubTr);
						if (pst) {
							ss.push(ms<fAstStackItem>(pst));
						}

					} else {
						ss.push(ms<fAstStackItem>(currNode->getAstRightN()));
					}
					continue;
				}
			}

			ss.pop();
			currNode->accept(shared_from_this(), prnSc);
			polishCalcSS->push_back(currNode);
		}
		prnSc->setPolishSS(std::move(polishCalcSS));
		std::cout << subTr->toString() + " END" << std::endl;
	}


	void  ZVisitor::visit(sp<fAstOptrNod> n, esc prnSc)  {
		assert(n != nullptr);
		std::cout << "Operator: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fAstOprndNod> n, esc prnSc)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}



}
