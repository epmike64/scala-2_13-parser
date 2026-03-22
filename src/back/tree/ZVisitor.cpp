
#include "back/tree/ZVisitor.hpp"

#include <iostream>

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
#include "ast/leaf/fValueDecl.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "util/fUUID.hpp"
#include "back/tree/ZVisitHelp.hpp"

namespace zebra::back::tree {

	void ZVisitor::visit() {
		std::cout << "--- Visitor starts ---" << std::endl;
		esc s = ms<ZEnclScope>(nullptr, ms<ZProgram>());
		compileUnit_->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fCompileUnit> n, esc prnSc)  {

		sp<ZCompileUnit> zcu = ms<ZCompileUnit>("ZCompileUnit_" + UUID::generate().toString());
		esc s = ms<ZEnclScope>(prnSc, zcu);

		if (n->getPackages().size() > 0) {
			std::string packgName;
			for (const auto& pkg : n->getPackages()) {
				packgName += pkg->getPackgQualName();
			}
			zcu->setPackage(packgName);
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

		std::cout << "Visiting "<< (cls->isCaseClass()? "Case ": "") <<"ClassDef "  << cls->getIdentName()  << std::endl;

		sp<ZClassDef> zClsDef = ms<ZClassDef>(cls->getIdentName());
		esc clsDefScp = ms<ZEnclScope>(prnSc, zClsDef);

		if (cls->getModifiers()) {
			cls->getModifiers()->accept(shared_from_this(), clsDefScp);
		}

		if (cls->getConstrAccessModifier()) {
			cls->getConstrAccessModifier()->accept(shared_from_this(), clsDefScp);
		}

		// if (cls->getTypeParamClause()) {
		// 	cls->getTypeParamClause()->accept(shared_from_this(), clsDefScp);
		// }

		if (cls->getClassParamClauses()) {
			cls->getClassParamClauses()->accept(shared_from_this(), clsDefScp);
		}

		if (cls->getExtendsTemplate()) {
			cls->getExtendsTemplate()->accept(shared_from_this(), clsDefScp);
		}
	}

	void ZVisitor::visit(sp<fObjectDef> obj, esc prnSc) {
		std::cout << "Visiting "<< (obj->isCaseClass()? "Case ": "") <<"Object"  << obj->getIdentName()  << std::endl;

		sp<ZObjectDef> zObjDef = ms<ZObjectDef>(obj->getIdentName());
		esc objDefScp = ms<ZEnclScope>(prnSc, zObjDef);

		if (obj->getModifiers()) {
			obj->getModifiers()->accept(shared_from_this(), objDefScp);
		}

		if (obj->getExtendsTemplate()) {
			obj->getExtendsTemplate()->accept(shared_from_this(), objDefScp);
		}
	}

	void ZVisitor::visit(sp<fClassTemplate> n, esc prnSc) {
		std::cout << "Visiting Class Template" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_CLASS_TEMPLATE);
		// if (n->getClassParents()) {
		// 	n->getClassParents()->accept(shared_from_this(), s);
		// }
		if (n->getTemplateBody()) {
			n->getTemplateBody()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTemplate> n, esc prnSc) {
		std::cout << "Visiting Template" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_TEMPLATE);
		if (n->getTemplateBody()) {
			n->getTemplateBody()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTemplateBody> n, esc prnSc) {
		std::cout << "Visiting Template Body" << std::endl;

		sp<ZTemplateBody> zTB = ms<ZTemplateBody>();
		esc tbScp = ms<ZEnclScope>(prnSc,  zTB);
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(shared_from_this(), tbScp);
		}
	}


	void ZVisitor::visit(sp<fParamClauses> n, esc prnSc) {

		for (auto paramList : n->getParamLists()) {
			for (auto param : paramList) {
				param->accept(shared_from_this(), prnSc);
			}
		}
		/*for (auto impicitParam: *n->getImplicitParamList()) {
			impicitParam->accept(shared_from_this(), prnSc);
		}*/
	}

	void ZVisitor::visit(sp<fClassParamClauses> n, esc prnSc) {
		for (const auto& classParamList : n->getClassParamLists()) {

			for (auto & classParam : classParamList) {
				classParam->accept(shared_from_this(), prnSc);
			}
		}
		/*
		for (const auto& implicitClassParam : n->getImplicitClassParamList()) {
			implicitClassParam->accept(shared_from_this(), prnSc);
		}*/
	}





	void ZVisitor::visit(sp<fParam> n, esc prnSc) {
		std::cout << "Visiting Parameter: " << n->getIdentToken()->toString() << std::endl;

		assert(prnSc->getLangConstruct() == Z_REG_FUNC || prnSc->getLangConstruct() == Z_THIS_FUNC);
		sp<ZParam> zParam = ms<ZParam>(n->getIdentName());

		esc zParamScp = ms<ZEnclScope>(prnSc,  zParam);
		n->getParamType()->accept(shared_from_this(), zParamScp);


		sp<fAstProdSubTreeN> assignExpr = n->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> zPSubTr = ms<ZProdSubTreeN>(Z_PARAM_DEFAULT_EXPR);
			esc zPSubTrScp = ms<ZEnclScope>(prnSc,  zPSubTr);

			assignExpr->accept(shared_from_this(), zPSubTrScp);
			zParam->setDefaultValueExpr(zPSubTr->getTreePostOrderSS());
		}

		sp<ZFunc> f = std::dynamic_pointer_cast<ZFunc>(prnSc->getZSymbol());
		f->addParam(zParam);
	}

	void ZVisitor::visit(sp<fClassParam> fClsPar, esc prnSc) {

		assert(prnSc->getLangConstruct() == Z_CLASS_DEF);

		sp<ZClassParam> clsParam = ms<ZClassParam>(fClsPar->getIdentName(), fClsPar->isMutable() );
		esc clsParamScp = ms<ZEnclScope>(prnSc,  clsParam);
		fClsPar->getParamType()->accept(shared_from_this(), clsParamScp);


		sp<fAstProdSubTreeN> assignExpr = fClsPar->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>(Z_CLASS_PARAM_DEFAULT_EXPR);
			esc pSubTrScp = ms<ZEnclScope>(prnSc,  pSubTr);

			assignExpr->accept(shared_from_this(), pSubTrScp);
			clsParam->setDefaultValueExpr(pSubTr->getTreePostOrderSS());
		}
		sp<ZClassDef> clsDef = std::dynamic_pointer_cast<ZClassDef>(prnSc->getZSymbol());
		clsDef->addClassParam(clsParam);
	}

	void ZVisitor::visit(sp<fParamType> n, esc prnSc) {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void  ZVisitor::visit(sp<fType> n, esc prnSc)  {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void ZVisitor::visit(sp<fTypeParamClause> n, esc prnSc) {

		esc clsScp = ZVisitHelp::getWrapScope(prnSc, Z_CLASS_DEF);

		for (auto typeParam : *n->getVariantTypeParams()) {

			sp<ZVariantTypeParam> z_vtp = ms<ZVariantTypeParam>();
			esc s = ms<ZEnclScope>(prnSc,  z_vtp);
			typeParam->accept(shared_from_this(), s);
		}
	}

	void ZVisitor::visit(sp<fVariantTypeParam> n, esc prnSc) {
		std::cout << "Visiting VariantTypeParam: " << n->toString() << std::endl;
	}


	void ZVisitor::visit(sp<fClassConstr> n, esc prnSc) {
		std::cout << "Visiting Class Constructor" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_CLASS_CONSTR);
		// n->getPrimaryCtorParamType()->accept(shared_from_this(), s);
		// if (n->getArgs()) {
		// 	std::cout << "Visiting Class Constructor Arguments" << std::endl;
		// 	n->getArgs()->accept(shared_from_this(), s);
		// }
	}



	void  ZVisitor::visit(sp<fValueDef> n, esc prnSc)  {
		std::cout << "Visiting Value Decl: " << n->toString() << std::endl;
		// assert(n->getNames().size() > 0);
		//
		// std::vector<sp<ZEnclScope>> esVec;// = ms<std::vector<EnclosingScope>>(prnSc, fLangGrmrProdE::VALUE_DEF);
		//
		// for (size_t i = 0; i < n->getNames().size(); i++) {
		// 	std::cout << "Visiting name " << i << " of value declaration" << std::endl;
		//
		// 	esVec.push_back(ms<ZEnclScope>(prnSc, Z_VALUE_DEF));
		// 	n->getNames()[i]->accept(shared_from_this(), esVec[i]);
		//
		// 	//prnSc->getPolishSS();
		// }
		//
		// if (n->getType()) {
		// 	n->getType()->accept(shared_from_this(), prnSc);
		// }
		//
		// if (n->getModifiers()) {
		// 	n->getModifiers()->accept(shared_from_this(), prnSc);
		// }
		//
		// sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		// if (assignExpr != nullptr) {
		// 	std::cout << "Visiting assignment expression for value declaration" << std::endl;
		// 	assignExpr->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fIf> n, esc prnSc) {
		std::cout << "-- IF Cond Expr" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_IF);
		//
		// n->getCondExpr()->accept(shared_from_this(), s);
		// std::cout << "-- IF Body Exp" << std::endl;
		// n->getIfBody()->accept(shared_from_this(), s);
		// if (n->getElseBody()) {
		// 	std::cout << "-- IF_ELSE Body Exp" << std::endl;
		// 	n->getElseBody()->accept(shared_from_this(), s);
		// }
	}

	void ZVisitor::visit(sp<fWhile > n, esc prnSc) {
		std::cout << "-- WHILE Cond Expr" << std::endl;
	// 	esc s = ms<ZEnclScope>(prnSc, Z_WHILE);
	//
	// 	n->getCondExpr()->accept(shared_from_this(), s);
	// 	std::cout << "-- WHILE Body Exp" << std::endl;
	// 	n->getBody()->accept(shared_from_this(), s);
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
		// // esc s = ms<ZEnclScope>(prnSc, Z_CASE_CLAUSE);
		//
		// n->getPattern()->accept(shared_from_this(), s);
		// if (n->getGuard()) {
		// 	std::cout << "Visiting Case Guard" << std::endl;
		// 	n->getGuard()->accept(shared_from_this(), s);
		// }
		// std::cout << "Visiting Case Body" << std::endl;
		// n->getBlock()->accept(shared_from_this(), s);
	}

	void ZVisitor::visit(sp<fCaseClauses> n, esc prnSc) {
		std::cout << "Visiting Case Clauses" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_CASE_CLAUSES);
		// for (const auto& clause : n->getCaseClauses()) {
		// 	clause->accept(shared_from_this(), prnSc);
		// }
	}








	void ZVisitor::visit(sp<fClassParents> n, esc prnSc) {
		std::cout << "Visiting Class Parents" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_CLASS_PARENTS);
		// if (n->getConstr()) {
		// 	n->getConstr()->accept(shared_from_this(), s);
		// }
		// if (n->getWithTypes()) {
		// 	n->getWithTypes()->accept(shared_from_this(), s);
		// }
	}



	void ZVisitor::visit(sp<fConstrBlock> n, esc prnSc) {
		std::cout << "Visiting Constructor Block" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_CONSTR_BLOCK);
		// if (n->getArgExprs()) {
		// 	std::cout << "Visiting Constructor Block Argument Expressions" << std::endl;
		// 	n->getArgExprs()->accept(shared_from_this(), s);
		// }
		// std::cout << "Visiting Constructor Block Statements" << std::endl;
		// for (const auto& stmt : n->getBlockStmts()) {
		// 	stmt->accept(shared_from_this(), s);
		// }
	}

	void ZVisitor::visit(sp<fFor> n, esc prnSc) {
		std::cout << "Visiting For Loop" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_FOR);
		// for (auto gen: n->getGenerators()) {
		// 	gen->accept(shared_from_this(), s);
		// }
		//
		// if (n->getYieldExpr()) {
		// 	std::cout << "Visiting For Loop Yield Expression" << std::endl;
		// 	n->getYieldExpr()->accept(shared_from_this(), prnSc);
		// }
	}

	void ZVisitor::visit(sp<fFunc> n, esc prnSc) {
		std::cout << "Visiting fFun" << std::endl;
		// sp<ZFunc> z_fun = ms<ZFunc>();
		// esc s = ms<ZEnclScope>(prnSc,  z_fun);
		// esc s = ms<ZEnclScope>(prnSc, Z_FFUN);
		// n->getModifiers()->accept(shared_from_this(), s);
	}



	void ZVisitor::visit(sp<fGenerator> n, esc prnSc) {
		std::cout << "Visiting Generator" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_GENERATOR);
		// if (n->isCaseGenerator()) {
		// 	std::cout << "Visiting Case Pattern" << std::endl;
		// 	n->getCasePattern1()->accept(shared_from_this(), s);
		// }
		// for (const auto& guard : n->getGuards()) {
		// 	std::cout << "Visiting Generator Guard" << std::endl;
		// 	guard->accept(shared_from_this(), s);
		// }
		// if (n->getInExpr()) {
		// 	std::cout << "Visiting Generator In Expression" << std::endl;
		// 	n->getInExpr()->accept(shared_from_this(), s);
		// }
		// for (const auto& endingPattern : n->getEndingPattern1s()) {
		// 	std::cout << "Visiting Generator Ending Pattern" << std::endl;
		// 	endingPattern->accept(shared_from_this(), s);
		// }
		// for (const auto& endingExpr : n->getEndingExprs()) {
		// 	std::cout << "Visiting Generator Ending Expression" << std::endl;
		// 	endingExpr->accept(shared_from_this(), s);
		// }
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



	void ZVisitor::visit(sp<fRegFunc> n, esc prnSc) {
		std::cout << "Visiting Named Function: " << n->getFunSig()->getIdentToken()->toString() << std::endl;
		sp<ZRegFunc> zFunc = ms<ZRegFunc>(n->getFunSig()->getIdentName());
		esc zFunScp = ms<ZEnclScope>(prnSc,  zFunc);

		// esc s = ms<ZEnclScope>(prnSc, Z_NAMED_FUN);
		// if (n->getModifiers()) {
		// 	n->getModifiers()->accept(shared_from_this(), s);
		// }

		n->getFunSig()->accept(shared_from_this(), zFunScp);

		// std::cout << "Visiting Named Function Body" << std::endl;
		// if (n->getFunBody()) {
		// 	n->getFunBody()->accept(shared_from_this(), s);
		// }
	}






	void ZVisitor::visit(sp<fOverrideModifier> n, esc prnSc) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}







	void ZVisitor::visit(sp<fParamTypes> n, esc prnSc) {
		std::cout << "Visiting Parameter Types" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_PARAM_TYPES);
		// if (n->getParamTypes()) {
		// 	for (auto ptp : *n->getParamTypes().get()) {
		// 		ptp->accept(shared_from_this(), s);
		// 	}
		// }
	}

	void ZVisitor::visit(sp<fFunSig> n, esc prnSc) {
		std::cout << "Visiting Function Signature: " << n->getIdentToken()->toString() << std::endl;

		// esc s = ms<ZEnclScope>(prnSc, Z_FUN_SIG);
		assert(prnSc->getLangConstruct() == Z_REG_FUNC);
		if (n->getParamClauses()) {
			n->getParamClauses()->accept(shared_from_this(), prnSc);
		}
		// if (n->getTypeParam()) {
		// 	std::cout << "Visiting Function Type Parameters" << std::endl;
		// 	auto typeParams = *n->getTypeParam().get();
		// 	for (auto tpp : typeParams) {
		// 			tpp->accept(shared_from_this(), prnSc);
		// 	}
		// }
	}

	void ZVisitor::visit(sp<fReturn> n, esc prnSc) {
		std::cout << "Visiting Return Statement" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_RETURN);
		// if (n->getReturnExpr()) {
		// 	std::cout << "Visiting Return Expression" << std::endl;
		// 	n->getReturnExpr()->accept(shared_from_this(), s);
		// }
	}



	void ZVisitor::visit(sp<fThisFunc> n, esc prnSc) {
		std::cout << "Visiting This Function" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_THIS_FUN);
		// if (n->getParamClauses()) {
		// 	std::cout << "Visiting Parameter Clauses of This Function" << std::endl;
		// 	n->getParamClauses()->accept(shared_from_this(), s);
		// }
		// if (n->getConstrBlock()) {
		// 	std::cout << "Visiting Constructor Block of This Function" << std::endl;
		// 	n->getConstrBlock()->accept(shared_from_this(), s);
		// }
	}

	void ZVisitor::visit(sp<fThrow> n, esc prnSc) {
		std::cout << "Visiting Throw" << std::endl;
		if (n->getThrowExpr()) {
			n->getThrowExpr()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTraitDef> n, esc prnSc) {
		std::cout << "Visiting Trait Definition: " << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_TRAIT_DEF);
		// if (n->getExtendsTemplate()) {
		// 	std::cout << "Visiting extends template of trait definition" << std::endl;
		// 	n->getExtendsTemplate()->accept(shared_from_this(), s);
		// }
	}

	void ZVisitor::visit(sp<fTry> n, esc prnSc) {
		std::cout << "Visiting Try Block" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_TRY);
		// n->getTryBlock()->accept(shared_from_this(), s);
		// // for (const auto& catchClause : n->getCatchClauses()) {
		// // 	std::cout << "Visiting Catch Clause" << std::endl;
		// // 	catchClause->accept(shared_from_this(), prnSc);
		// // }
		// if (n->getFinallyBlock()) {
		// 	std::cout << "Visiting Finally Block" << std::endl;
		// 	n->getFinallyBlock()->accept(shared_from_this(), s);
		// }
	}

	void ZVisitor::visit(sp<fTypeArgs> n, esc prnSc) {
		std::cout << "Visiting Type Arguments" << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_TYPE_ARGS);
		// for (const auto& typeArg : n->getTypeArgs()) {
		// 	typeArg->accept(shared_from_this(), s);
		// }
	}
	void ZVisitor::visit(sp<fTypeDef> n, esc prnSc) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
		// esc s = ms<ZEnclScope>(prnSc, Z_TYPE_DEF);
		// if (n->getAssignedType()) {
		// 	std::cout << "Visiting Assigned Type of Type Definition" << std::endl;
		// 	 n->getAssignedType()->accept(shared_from_this(), s);
		// }
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
		// esc s = ms<ZEnclScope>(prnSc, Z_VALUE_DECL);
		// for (auto name: n->getNames()) {
		// 	std::cout << "Visiting name of value declaration" << std::endl;
		// 	name->accept(shared_from_this(), s);
		// }
		//
		// if (n->getType()) {
		// 	std::cout << "Visiting Type of Value Declaration" << std::endl;
		// 	n->getType()->accept(shared_from_this(), prnSc);
		// }
		//
		//  sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		// if (assignExpr != nullptr) {
		// 	std::cout << "Visiting assignment expression for value declaration" << std::endl;
		// 	assignExpr->accept(shared_from_this(), prnSc);
		// }
	}



	sp<fAstNod> ZVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree) {
		return ZVisitHelp::getAstPSTreeRightN(subTree);
	}

	void ZVisitor::visit(sp<fAstProdSubTreeN> subTr, esc prnSc) {
		ZVisitHelp::traverseProdSubTree(subTr, prnSc, shared_from_this());
	}




	void  ZVisitor::visit(sp<fAstOprndNod> n, esc prnSc)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}

	/**
	 *
	 *  FOR LATER
	 */

	void  ZVisitor::visit(sp<fAstOptrNod> n, esc prnSc)  {
		std::cout << "Operator: " << n->toString() << std::endl;
		ZVisitHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fLiteral> n, esc prnSc)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
		ZVisitHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fStableId>n, esc prnSc)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
		ZVisitHelp::treePostOrderPush(n, prnSc);
	}



	/**
	 *
	 * DONE
	 */
	void ZVisitor::visit(sp<fPackage> n, esc prnSc) {}
	void ZVisitor::visit(sp<fImport> n, esc prnSc) {

		sp<std::vector<std::string>> imports_ = ms<std::vector<std::string>>();
		for (sp<fImportExpr>& impExpr : n->getImportExprs()) {
			std::string qualName = impExpr->getId()->getQualName();
			if (impExpr->getUnderscore()) {
				qualName += "._";
				imports_->emplace_back(std::move(qualName));
			} else if (impExpr->getSelectors()) {

				for (size_t i = 0; i < impExpr->getSelectors()->size(); i++) {
					std::string qualNameSel =  qualName + "." + impExpr->getSelectors()->at(i)->getFrom()->toString();
					imports_->emplace_back(std::move(qualNameSel));
				}
			}
		}
		sp<I_Imports> im = std::dynamic_pointer_cast<I_Imports>(prnSc->getZSymbol());
		im->addImports(imports_);
	}
}
