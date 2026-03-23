
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
#include "back/tree/ZVisitClassHelp.hpp"
#include "back/tree/ZVisitFuncHelp.hpp"
#include "util/fUUID.hpp"
#include "back/tree/ZVisitPSubTreeHelp.hpp"
#include "back/tree/ZVisitBlockHelp.hpp"
#include "back/tree/ZVisitParamHelp.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"

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
			esc imScp = ms<ZEnclScope>(prnSc, zcu->getImportList());
			for (const auto& imp : n->getImports()) {
				imp->accept(shared_from_this(), imScp);
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
		ZVisitClassHelp::visitClassDef(cls, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fObjectDef> obj, esc prnSc) {
		ZVisitClassHelp::visitObjectDef(obj, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassTemplate> n, esc prnSc) {
		ZVisitClassHelp::visitClassTemplate(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplate> n, esc prnSc) {
		ZVisitClassHelp::visitTemplate(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTemplateBody> n, esc prnSc) {
		ZVisitClassHelp::visitTemplateBody(n, prnSc, shared_from_this());
	}


	void ZVisitor::visit(sp<fParamClauses> n, esc prnSc) {

		for (auto paramList : n->getParamLists()) {
			for (auto param : paramList) {
				param->accept(shared_from_this(), prnSc);
			}
		}
		if (n->getImplicitParamList()) {
			for (auto impicitParam: *n->getImplicitParamList()) {
				impicitParam->accept(shared_from_this(), prnSc);
			}
		}
	}

	void ZVisitor::visit(sp<fClassParamClauses> n, esc prnSc) {
		ZVisitParamHelp::visitClassParamClauses(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTypeParamClause> n, esc prnSc) {
		ZVisitTypeParamHelp::visitTypeParamClauses(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fVariantTypeParam> n, esc prnSc) {
		ZVisitTypeParamHelp::visitVariantTypeParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fParam> n, esc prnSc) {
		ZVisitParamHelp::visitParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fClassParam> n, esc prnSc) {
		ZVisitParamHelp::visitClassParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fParamType> n, esc prnSc) {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void  ZVisitor::visit(sp<fType> n, esc prnSc)  {
		n->getTypeTree()->accept(shared_from_this(), prnSc);
	}

	void ZVisitor::visit(sp<fClassConstr> n, esc prnSc) {
		std::cout << "Visiting Class Constructor" << std::endl;
	}

	void  ZVisitor::visit(sp<fValueDef> n, esc prnSc)  {
		std::cout << "Visiting Value Decl: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fIf> n, esc prnSc) {
		std::cout << "-- IF Cond Expr" << std::endl;
	}

	void ZVisitor::visit(sp<fWhile > n, esc prnSc) {
		std::cout << "-- WHILE Cond Expr" << std::endl;
	}

	void ZVisitor::visit(sp<fAccessModifier> n, esc prnSc) {
		std::cout << "Visiting Access Modifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fAccessQualifier> n, esc prnSc) {
		std::cout << "Visiting Access Qualifier: " << n->toString() << std::endl;
	}
	void ZVisitor::visit(sp<fBlock> n, esc prnSc) {
		ZVisitBlockHelp::visitBlock(n, prnSc, shared_from_this());

	}
	void ZVisitor::visit(sp<fCaseClause> n, esc prnSc) {
		std::cout << "Visiting Case Clause" << std::endl;
	}

	void ZVisitor::visit(sp<fCaseClauses> n, esc prnSc) {
		std::cout << "Visiting Case Clauses" << std::endl;
	}

	void ZVisitor::visit(sp<fClassParents> n, esc prnSc) {
		std::cout << "Visiting Class Parents" << std::endl;
	}

	void ZVisitor::visit(sp<fConstrBlock> n, esc prnSc) {
		std::cout << "Visiting Constructor Block" << std::endl;
	}

	void ZVisitor::visit(sp<fFor> n, esc prnSc) {
		std::cout << "Visiting For Loop" << std::endl;
	}

	void ZVisitor::visit(sp<fFunc> n, esc prnSc) {
		std::cout << "Visiting fFun" << std::endl;
		throw std::runtime_error("Unimplemented");
	}

	void ZVisitor::visit(sp<fGenerator> n, esc prnSc) {
		std::cout << "Visiting Generator" << std::endl;
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

	void ZVisitor::visit(sp<fRegFunc> fun, esc prnSc) {
		ZVisitFuncHelp::visitRegFunc(fun, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fOverrideModifier> n, esc prnSc) {
		std::cout << "Visiting Override Modifier: " << n->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fParamTypes> n, esc prnSc) {
		ZVisitParamHelp::visitParamTypes(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fFunSig> n, esc prnSc) {
		ZVisitFuncHelp::visitFunSig(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fReturn> n, esc prnSc) {
		std::cout << "Visiting Return Statement" << std::endl;
	}

	void ZVisitor::visit(sp<fThisFunc> n, esc prnSc) {
		ZVisitFuncHelp::visitThisFunc(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fThrow> n, esc prnSc) {
		std::cout << "Visiting Throw" << std::endl;
		if (n->getThrowExpr()) {
			n->getThrowExpr()->accept(shared_from_this(), prnSc);
		}
	}

	void ZVisitor::visit(sp<fTraitDef> n, esc prnSc) {
		ZVisitClassHelp::visitTraitDef(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fTry> n, esc prnSc) {
		std::cout << "Visiting Try Block" << std::endl;
	}

	void ZVisitor::visit(sp<fTypeArgs> n, esc prnSc) {
		std::cout << "Visiting Type Arguments" << std::endl;

	}
	void ZVisitor::visit(sp<fTypeDef> n, esc prnSc) {
		std::cout << "Visiting Type Definition: " << n->getTypeDefName()->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fTypeParam> n, esc prnSc) {
		ZVisitTypeParamHelp::visitTypeParam(n, prnSc, shared_from_this());
	}

	void ZVisitor::visit(sp<fUnderscore> n, esc prnSc) {
		std::cout << "Visiting Underscore: " <<n ->toString() << std::endl;
	}

	void ZVisitor::visit(sp<fValue> n, esc prnSc) {
		std::cout << "Visiting Value: " << std::endl;
	}

	void ZVisitor::visit(sp<fValueDecl> n, esc prnSc) {
		std::cout << "Visiting Value Declaration: " << std::endl;
	}

	sp<fAstNod> ZVisitor::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree) {
		return ZVisitPSubTreeHelp::getAstPSTreeRightN(subTree);
	}

	void ZVisitor::visit(sp<fAstProdSubTreeN> subTr, esc prnSc) {
		ZVisitPSubTreeHelp::traverseProdSubTree(subTr, prnSc, shared_from_this());
	}


	void  ZVisitor::visit(sp<fAstOprndNod> n, esc prnSc)  {
		assert(n != nullptr && n->getAstLeftN() == nullptr && n->getAstRightN() == nullptr);
		std::cout << "Operand: " << n->toString() << std::endl;
	}

	void  ZVisitor::visit(sp<fAstOptrNod> n, esc prnSc)  {
		std::cout << "Operator: " << n->toString() << std::endl;
		ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fLiteral> n, esc prnSc)  {
		std::cout << "Visiting Literal: " << n->toString() << std::endl;
		ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}

	void  ZVisitor::visit(sp<fStableId>n, esc prnSc)  {
		std::cout << "Visiting StableId: " << n->toString() << std::endl;
		ZVisitPSubTreeHelp::treePostOrderPush(n, prnSc);
	}


	void ZVisitor::visit(sp<fPackage> n, esc prnSc) {}

	void ZVisitor::visit(sp<fImport> n, esc prnSc) {

		sp<ZImport> zim =  ms<ZImport>();
		for (sp<fImportExpr>& impExpr : n->getImportExprs()) {
			std::string qualName = impExpr->getId()->getQualName();
			if (impExpr->getUnderscore()) {
				qualName += "._";
				zim->addImport(std::move(qualName));
			} else if (impExpr->getSelectors()) {

				for (size_t i = 0; i < impExpr->getSelectors()->size(); i++) {
					std::string qualNameSel =  qualName + "." + impExpr->getSelectors()->at(i)->getFrom()->toString();
					zim->addImport(std::move(qualNameSel));
				}
			} else {
				zim->addImport(std::move(qualName));
			}
		}

		sp<ZImportList> imList = std::dynamic_pointer_cast<ZImportList>(prnSc->getZSymbol());
		imList->addImport(zim);
	}
}
