
#include "ast/tree/fLangAstVisitor.hpp"

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
#include "ast/leaf/fValueDecl.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/node/fLangTree.hpp"

namespace zebra::ast::tree {



	void fLangAstVisitor::visit() {
		std::cout << "Visitor starts" << std::endl;
		esc s = ms<EnclosingScope>();
		compileUnit_->accept(shared_from_this(), s);
	}

	void fLangAstVisitor::visit(sp<fCompileUnit> n, esc s)  {
		std::cout << "Visiting Compile Unit" << std::endl;
		if (n->getPackages().size() > 0) {
			std::cout << "Visiting Packages in Compile Unit" << std::endl;
			for (const auto& pkg : n->getPackages()) {
				pkg->accept(shared_from_this(), s);
			}
		}
		if (n->getImports().size() > 0) {
			std::cout << "Visiting Imports in Compile Unit" << std::endl;
			for (const auto& imp : n->getImports()) {
				imp->accept(shared_from_this(), s);
			}
		}
		if (n->getStmts().size() > 0) {
			std::cout << "Visiting Statements in Compile Unit" << std::endl;
			for (const auto& stmt : n->getStmts()) {
				stmt->accept(shared_from_this(), s);
			}
		}
	}

	void  fLangAstVisitor::visit(sp<fClassDef> cls, esc s){
		std::cout << "Visiting Class Definition: " << cls->getName()->toString() << std::endl;
		if (cls->getExtendsTemplate()) {
			std::cout << "Visiting extends template of class definition" << std::endl;
			cls->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void  fLangAstVisitor::visit(sp<fLiteral> n, esc s)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
	}

	void  fLangAstVisitor::visit(sp<fStableId>n, esc s)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
	}

	void  fLangAstVisitor::visit(sp<fType> n, esc s)  {
		std::cout << n->toString() << std::endl;
	}

	void  fLangAstVisitor::visit(sp<fValueDef> n, esc s)  {
		std::cout << "Visiting Value Decl: " << n->toString() << std::endl;

		for (size_t i = 0; i < n->getNames().size(); i++) {
			std::cout << "Visiting name " << i << " of value declaration" << std::endl;
			n->getNames()[i]->accept(shared_from_this(), s);
		}

		sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value declaration" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fIf> n, esc s) {
		std::cout << "-- IF Cond Expr" << std::endl;
		n->getCondExpr()->accept(shared_from_this(), s);
		std::cout << "-- IF Body Exp" << std::endl;
		n->getIfBody()->accept(shared_from_this(), s);
		if (n->getElseBody()) {
			std::cout << "-- IF_ELSE Body Exp" << std::endl;
			n->getElseBody()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fWhile > n, esc s) {
		std::cout << "-- WHILE Cond Expr" << std::endl;
		n->getCondExpr()->accept(shared_from_this(), s);
		std::cout << "-- WHILE Body Exp" << std::endl;
		n->getBody()->accept(shared_from_this(), s);
	}

	void fLangAstVisitor::visit(sp<fAccessModifier> n, esc s) {
		std::cout << "Visiting Access Modifier: " << n->toString() << std::endl;
	}
	void fLangAstVisitor::visit(sp<fAccessQualifier> n, esc s) {
		std::cout << "Visiting Access Qualifier: " << n->toString() << std::endl;
	}
	void fLangAstVisitor::visit(sp<fBlock> n, esc s) {
		std::cout << "Visiting Block" << std::endl;
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fCaseClause> n, esc s) {
		std::cout << "Visiting Case Clause" << std::endl;
		n->getPattern()->accept(shared_from_this(), s);
		if (n->getGuard()) {
			std::cout << "Visiting Case Guard" << std::endl;
			n->getGuard()->accept(shared_from_this(), s);
		}
		std::cout << "Visiting Case Body" << std::endl;
		n->getBlock()->accept(shared_from_this(), s);
	}

	void fLangAstVisitor::visit(sp<fCaseClauses> n, esc s) {
		std::cout << "Visiting Case Clauses" << std::endl;
		for (const auto& clause : n->getCaseClauses()) {
			clause->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fClassConstr> n, esc s) {
		std::cout << "Visiting Class Constructor" << std::endl;
		n->getPrimaryCtorParamType()->accept(shared_from_this(), s);
		if (n->getArgs()) {
			std::cout << "Visiting Class Constructor Arguments" << std::endl;
			n->getArgs()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fClassParam> n, esc s) {
		std::cout << "Visiting Class Parameter: " << n->getIdentifier()->toString() << std::endl;
		n->getParamType()->accept(shared_from_this(), s);

		sp<fAstProdSubTreeN> assignExpr = n->getDefaultValueExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for class parameter" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fClassParamClauses> n, esc s) {
		std::cout << "Visiting Class Parameter Clauses" << std::endl;
		for (const auto& paramClauseList : n->getClassParams()) {
			for (auto & paramClause : paramClauseList) {
				std::cout << "Visiting Class Parameter Clause" << std::endl;
				paramClause->accept(shared_from_this(), s);
			}
		}
	}

	void fLangAstVisitor::visit(sp<fClassParents> n, esc s) {
		std::cout << "Visiting Class Parents" << std::endl;
		if (n->getConstr()) {
			n->getConstr()->accept(shared_from_this(), s);
		}
		if (n->getWithTypes()) {
			n->getWithTypes()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fClassTemplate> n, esc s) {
		std::cout << "Visiting Class Template" << std::endl;
		if (n->getClassParents()) {
			n->getClassParents()->accept(shared_from_this(), s);
		}
		if (n->getTemplateBody()) {
			n->getTemplateBody()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fConstrBlock> n, esc s) {
		std::cout << "Visiting Constructor Block" << std::endl;
		if (n->getArgExprs()) {
			std::cout << "Visiting Constructor Block Argument Expressions" << std::endl;
			n->getArgExprs()->accept(shared_from_this(), s);
		}
		std::cout << "Visiting Constructor Block Statements" << std::endl;
		for (const auto& stmt : n->getBlockStmts()) {
			stmt->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fFor> n, esc s) {
		std::cout << "Visiting For Loop" << std::endl;
		for (auto gen: n->getGenerators()) {
			gen->accept(shared_from_this(), s);
		}

		if (n->getYieldExpr()) {
			std::cout << "Visiting For Loop Yield Expression" << std::endl;
			n->getYieldExpr()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fFun> n, esc s) {
		std::cout << "Visiting fFun" << std::endl;
		n->getModifiers()->accept(shared_from_this(), s);
	}

	void fLangAstVisitor::visit(sp<fFunSig> n, esc s) {
		std::cout << "Visiting Function Signature: " << n->getFunName()->toString() << std::endl;
		if (n->getParamClauses()) {
			std::cout << "Visiting Function Parameter Clauses" << std::endl;
			n->getParamClauses()->accept(shared_from_this(), s);
		}
		if (n->getTypeParam()) {
			std::cout << "Visiting Function Type Parameters" << std::endl;
			auto typeParams = *n->getTypeParam().get();
			for (auto tpp : typeParams) {
					tpp->accept(shared_from_this(), s);
			}
		}
	}

	void fLangAstVisitor::visit(sp<fGenerator> n, esc s) {
		std::cout << "Visiting Generator" << std::endl;
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
	void fLangAstVisitor::visit(sp<fId> n, esc s) {
		std::cout << "Visiting Identifier: " << n->toString() << std::endl;
	}
	void fLangAstVisitor::visit(sp<fIds> n, esc s) {
		std::cout << "Visiting Identifiers" << std::endl;
		for (const auto& id : n->getIds()) {
			id->accept(shared_from_this(), s);
		}
	}
	// void fLangAstVisitor::visit(sp<fIf> n, esc s) {}
	void fLangAstVisitor::visit(sp<fImport> n, esc s) {
		std::cout << "Visiting Import: " << n->toString() << std::endl;
	}
	// void fLangAstVisitor::visit(sp<fLiteral> n, esc s) {}
	void fLangAstVisitor::visit(sp<fLocalModifier> n, esc s) {
		std::cout << "Visiting Local Modifier: " << n->toString() << std::endl;
	}
	void fLangAstVisitor::visit(sp<fModifier> n, esc s) {
		std::cout << "Visiting Modifier: " << n->toString() << std::endl;
	}
	void fLangAstVisitor::visit(sp<fModifiers> n, esc s) {
		std::cout << "Visiting Modifiers" << std::endl;
		if (n->getAccessModifier()) {
			std::cout << "Visiting Access Modifier in Modifiers" << std::endl;
			n->getAccessModifier()->accept(shared_from_this(), s);
		}
		if (n->getOverrideModifier()) {
			std::cout << "Visiting Override Modifier in Modifiers" << std::endl;
			n->getOverrideModifier()->accept(shared_from_this(), s);
		}
		if (n->getLocalModifier()) {
			std::cout << "Visiting Local Modifier in Modifiers" << std::endl;
			n->getLocalModifier()->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fNamedFun> n, esc s) {
		std::cout << "Visiting Named Function: " << n->getFunSig()->getFunName()->toString() << std::endl;
		n->getFunSig()->accept(shared_from_this(), s);
		std::cout << "Visiting Named Function Body" << std::endl;
		n->getFunBody()->accept(shared_from_this(), s);
	}

	void fLangAstVisitor::visit(sp<fObject> n, esc s) {
		if (n->isCaseClass()) {
			std::cout << "Visiting Case Class: " << n->getObjectName()->toString()  << std::endl;
		} else {
			std::cout << "Visiting Class: " << n->getObjectName()->toString() << std::endl;
		}
		if (n->getModifiers()) {
			n->getModifiers()->accept(shared_from_this(), s);
		}
		if (n->getExtendsTemplate()) {
			n->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fOverrideModifier> n, esc s) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}

	void fLangAstVisitor::visit(sp<fPackage> n, esc s) {
		std::cout << "Visiting Package: " << n->toString() << std::endl;
	}

	void fLangAstVisitor::visit(sp<fParam> n, esc s) {
		std::cout << "Visiting Parameter: " << n->getIdentifier()->toString() << std::endl;
		 sp<fAstProdSubTreeN> assignExpr = n->getDefaultValue();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for parameter" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fParamClauses> n, esc s) {
		std::cout << "Visiting Parameter Clauses" << std::endl;
		for (auto paramV : n->getParams()) {
			for (auto param : paramV) {
				std::cout << "Visiting Parameter Clause" << std::endl;
				param->accept(shared_from_this(), s);
			}
		}
	}

	void fLangAstVisitor::visit(sp<fParamType> n, esc s) {
		std::cout << "Visiting Parameter Type" << std::endl;
		if (n->getType()) {
			n->getType()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fParamTypes> n, esc s) {
		std::cout << "Visiting Parameter Types" << std::endl;

		if (n->getParamTypes()) {
			for (auto ptp : *n->getParamTypes().get()) {
				ptp->accept(shared_from_this(), s);
			}
		}
	}

	void fLangAstVisitor::visit(sp<fReturn> n, esc s) {
		std::cout << "Visiting Return Statement" << std::endl;
		if (n->getReturnExpr()) {
			std::cout << "Visiting Return Expression" << std::endl;
			n->getReturnExpr()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTemplate> n, esc s) {
		std::cout << "Visiting Template" << std::endl;
		if (n->getTemplateBody()) {
			std::cout << "Visiting Template Body of Template" << std::endl;
			 n->getTemplateBody()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTemplateBody> n, esc s) {
		std::cout << "Visiting Template Body" << std::endl;
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fThisFun> n, esc s) {
		std::cout << "Visiting This Function" << std::endl;
		if (n->getParamClauses()) {
			std::cout << "Visiting Parameter Clauses of This Function" << std::endl;
			n->getParamClauses()->accept(shared_from_this(), s);
		}
		if (n->getConstrBlock()) {
			std::cout << "Visiting Constructor Block of This Function" << std::endl;
			n->getConstrBlock()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fThrow> n, esc s) {
		std::cout << "Visiting Throw" << std::endl;
		if (n->getThrowExpr()) {
			n->getThrowExpr()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTraitDef> n, esc s) {
		std::cout << "Visiting Trait Definition: " << n->getName()->toString() << std::endl;
		if (n->getExtendsTemplate()) {
			std::cout << "Visiting extends template of trait definition" << std::endl;
			n->getExtendsTemplate()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTry> n, esc s) {
		std::cout << "Visiting Try Block" << std::endl;
		n->getTryBlock()->accept(shared_from_this(), s);
		// for (const auto& catchClause : n->getCatchClauses()) {
		// 	std::cout << "Visiting Catch Clause" << std::endl;
		// 	catchClause->accept(shared_from_this(), s);
		// }
		if (n->getFinallyBlock()) {
			std::cout << "Visiting Finally Block" << std::endl;
			n->getFinallyBlock()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTypeArgs> n, esc s) {
		std::cout << "Visiting Type Arguments" << std::endl;
		for (const auto& typeArg : n->getTypeArgs()) {
			typeArg->accept(shared_from_this(), s);
		}
	}
	void fLangAstVisitor::visit(sp<fTypeDef> n, esc s) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
		if (n->getAssignedType()) {
			std::cout << "Visiting Assigned Type of Type Definition" << std::endl;
			 n->getAssignedType()->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fTypeParam> n, esc s) {
		std::cout << "Visiting Type Parameter: " << n->getTypeParamName()->toString() << std::endl;
		// if (n->getTypeBound()) {
		// 	std::cout << "Visiting Type Bound for Type Parameter" << std::endl;
		// 	n->getTypeBound()->accept(shared_from_this(), s);
		// }
	}

	void fLangAstVisitor::visit(sp<fUnderscore> n, esc s) {
		std::cout << "Visiting Underscore" << std::endl;
	}

	void fLangAstVisitor::visit(sp<fValue> n, esc s) {
		// std::cout << "Visiting Value: " << n->getName()->toString() << std::endl;
		 sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fValueDecl> n, esc s) {
		std::cout << "Visiting Value Declaration: " << std::endl;

		for (auto name: n->getNames()) {
			std::cout << "Visiting name of value declaration" << std::endl;
			name->accept(shared_from_this(), s);
		}

		if (n->getType()) {
			std::cout << "Visiting Type of Value Declaration" << std::endl;
			n->getType()->accept(shared_from_this(), s);
		}

		 sp<fAstProdSubTreeN> assignExpr = n->getAssignExpr();
		if (assignExpr != nullptr) {
			std::cout << "Visiting assignment expression for value declaration" << std::endl;
			assignExpr->accept(shared_from_this(), s);
		}
	}

	void fLangAstVisitor::visit(sp<fVariantTypeParam> n, esc s) {
		std::cout << "Visiting Variant Type Parameter: " << n->getTypeParamName()->toString() << std::endl;
		// if (n->getTypeBound()) {
		// 	std::cout << "Visiting Type Bound for Variant Type Parameter" << std::endl;
		// 	n->getTypeBound()->accept(shared_from_this(), s);
		// }
	}


	sp<fAstNod> fLangAstVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTr) {
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

	// static sp<std::stack<sp<fLangTrBranch>>> lbrSS_;

	void fLangAstVisitor::visit(sp<fAstProdSubTreeN> subTr,  esc s) {

		s->setLbrSS(nullptr);

		std::cout << subTr->toString() << std::endl;
		std::stack<sp<fAstStackItem>> ss;
		sp<fAstNod> psubT = getAstPSTreeRightN(subTr);
		if (!psubT) {
			return;
		}

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
			currNode->accept(shared_from_this(), s);
			sp<fAstOprndNod> oprn = std::dynamic_pointer_cast<fAstOprndNod>(currNode);
			if (oprn) {
				if (!s->getLbrSS()) {
					s->setLbrSS(ms<std::stack<sp<fLangTrBranch>>>());
					s->getLbrSS()->push(ms<fLangTrBranch>(oprn));
				} else {
					s->getLbrSS()->top()->setRight(oprn);
				}
			}
			else {
				if (s->getLbrSS().get()->size() == 0) {
					throw std::runtime_error("Operator node expected to have a parent operator node in AST traversal");
				}
				sp<fLangTrBranch> top = s->getLbrSS()->top();
				top->setOptr(std::dynamic_pointer_cast<fAstOptrNod>(currNode));
				if (s->getLbrSS()->size() > 1) {
					s->getLbrSS()->pop();
					s->getLbrSS()->top()->setRight(top);
				}
			}
		}
		std::cout << subTr->toString() + " END" << std::endl;
	}


	void  fLangAstVisitor::visit(sp<fAstOptrNod> n, esc s)  {
		assert(n != nullptr);
		std::cout << "Operator: " << n->toString() << std::endl;
	}

	void  fLangAstVisitor::visit(sp<fAstOprndNod> n, esc s)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}



}
