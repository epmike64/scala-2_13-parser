
#pragma once

#include <iostream>

#include "../node/fAstNod.hpp"
#include "../node/fAstNodKndE.hpp"

#include <memory>
#include <stack>
#include <stdexcept>
#include <typeinfo>

#include "../node/fAstNodVisitor.hpp"
#include "ast/leaf/fCompileUnit.hpp"
#include "ast/leaf/fClassDef.hpp"
#include "ast/leaf/fIf.hpp"
#include "ast/leaf/fLiteral.hpp"
#include "ast/leaf/fStableId.hpp"
#include "ast/leaf/fType.hpp"
#include "ast/leaf/fValueDef.hpp"
#include "ast/leaf/fWhile.hpp"
#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fClassConstr.hpp"
#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fFun.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fImport.hpp"
#include "ast/leaf/fModifier.hpp"
#include "ast/leaf/fPackage.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fTypeArgs.hpp"


namespace zebra::ast::tree {

	using namespace ast::node;
	using namespace ast::leaf;

	class fLangAstVisitor : public fAstNodVisitor, public std::enable_shared_from_this<fLangAstVisitor> {
	protected:
		sp<fCompileUnit> compileUnit_;
		sp<fAstNod> getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree);

	public:
		explicit fLangAstVisitor(sp<fCompileUnit> cu, EnclsScope) : compileUnit_(cu){}
		void visit() override;
		void visit(sp<fCompileUnit>, EnclsScope)  override;
		//
		void visit(sp<fAstOptrNod>, EnclsScope)  override;
		void visit(sp<fAstOprndNod>, EnclsScope)  override;
		void visit(sp<fAstProdSubTreeN>, EnclsScope)  override;
		//-- Leaf node visit methods
		void visit(sp<fAccessModifier>, EnclsScope)  override;
		 void visit(sp<fAccessQualifier>, EnclsScope)  override;
		 void visit(sp<fBlock>, EnclsScope)  override;
		 void visit(sp<fCaseClause>, EnclsScope)  override;
		 void visit(sp<fCaseClauses>, EnclsScope)  override;
		 void visit(sp<fClassConstr>, EnclsScope)  override;
		 void visit(sp<fClassDef>, EnclsScope)  override;
		 void visit(sp<fClassParam>, EnclsScope)  override;
		 void visit(sp<fClassParamClauses>, EnclsScope)  override;
		 void visit(sp<fClassParents>, EnclsScope)  override;
		 void visit(sp<fClassTemplate>, EnclsScope)  override;
		 void visit(sp<fConstrBlock>, EnclsScope)  override;
		 void visit(sp<fFor>, EnclsScope)  override;
		 void visit(sp<fFun>, EnclsScope)  override;
		 void visit(sp<fFunSig>, EnclsScope)  override;
		 void visit(sp<fGenerator>, EnclsScope)  override;
		 void visit(sp<fId>, EnclsScope)  override;
		 void visit(sp<fIds>, EnclsScope)  override;
		 void visit(sp<fIf>, EnclsScope)  override;
		 void visit(sp<fImport>, EnclsScope)  override;
		 void visit(sp<fLiteral>, EnclsScope)  override;
		 void visit(sp<fLocalModifier>, EnclsScope)  override;
		 void visit(sp<fModifier>, EnclsScope)  override;
		 void visit(sp<fModifiers>, EnclsScope)  override;
		 void visit(sp<fNamedFun>, EnclsScope)  override;
		 void visit(sp<fObject>, EnclsScope)  override;
		 void visit(sp<fOverrideModifier>, EnclsScope)  override;
		 void visit(sp<fPackage>, EnclsScope)  override;
		 void visit(sp<fParam>, EnclsScope)  override;
		 void visit(sp<fParamClauses>, EnclsScope)  override;
		 void visit(sp<fParamType>, EnclsScope)  override;
		 void visit(sp<fParamTypes>, EnclsScope)  override;
		 void visit(sp<fReturn>, EnclsScope)  override;
		 void visit(sp<fStableId>, EnclsScope)  override;
		 void visit(sp<fTemplate>, EnclsScope)  override;
		 void visit(sp<fTemplateBody>, EnclsScope)  override;
		 void visit(sp<fThisFun>, EnclsScope)  override;
		 void visit(sp<fThrow>, EnclsScope)  override;
		 void visit(sp<fTraitDef>, EnclsScope)  override;
		 void visit(sp<fTry>, EnclsScope)  override;
		 void visit(sp<fType>, EnclsScope)  override;
		 void visit(sp<fTypeArgs>, EnclsScope)  override;
		 void visit(sp<fTypeDef>, EnclsScope)  override;
		 void visit(sp<fTypeParam>, EnclsScope)  override;
		 void visit(sp<fUnderscore>, EnclsScope)  override;
		 void visit(sp<fValue>, EnclsScope)  override;
		 void visit(sp<fValueDecl>, EnclsScope)  override;
		 void visit(sp<fValueDef>, EnclsScope)  override;
		 void visit(sp<fVariantTypeParam>, EnclsScope)  override;
		 void visit(sp<fWhile>, EnclsScope)  override;

	};
}
