
#pragma once

#include <iostream>

#include "../node/fAstNod.hpp"
#include "../node/fAstNodKndE.hpp"

#include <memory>
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


namespace zebra::ast::node {

	using namespace ast::leaf;

	class fLangAstVisitor : public fAstNodVisitor, public std::enable_shared_from_this<fLangAstVisitor> {
	protected:
		sp<fCompileUnit> compileUnit_;
		sp<fAstNod> getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree);

	public:
		explicit fLangAstVisitor(sp<fCompileUnit> cu) : compileUnit_(cu){}
		void visit() override;
		void visit(sp<fCompileUnit>) override;
		//
		void visit(sp<fAstOptrNod>) override;
		void visit(sp<fAstOprndNod>) override;
		void visit(sp<fAstProdSubTreeN>) override;
		//-- Leaf node visit methods
		void visit(sp<fAccessModifier> ) override;
		 void visit(sp<fAccessQualifier> ) override;
		 void visit(sp<fBlock> ) override;
		 void visit(sp<fCaseClause> ) override;
		 void visit(sp<fCaseClauses> ) override;
		 void visit(sp<fClassConstr> ) override;
		 void visit(sp<fClassDef>) override;
		 void visit(sp<fClassParam>) override;
		 void visit(sp<fClassParamClauses>) override;
		 void visit(sp<fClassParents>) override;
		 void visit(sp<fClassTemplate>) override;
		 void visit(sp<fConstrBlock>) override;
		 void visit(sp<fFor>) override;
		 void visit(sp<fFun>) override;
		 void visit(sp<fFunSig>) override;
		 void visit(sp<fGenerator>) override;
		 void visit(sp<fId>) override;
		 void visit(sp<fIds>) override;
		 void visit(sp<fIf>) override;
		 void visit(sp<fImport>) override;
		 void visit(sp<fLiteral>) override;
		 void visit(sp<fLocalModifier>) override;
		 void visit(sp<fModifier>) override;
		 void visit(sp<fModifiers>) override;
		 void visit(sp<fNamedFun>) override;
		 void visit(sp<fObject>) override;
		 void visit(sp<fOverrideModifier>) override;
		 void visit(sp<fPackage>) override;
		 void visit(sp<fParam> ) override;
		 void visit(sp<fParamClauses> ) override;
		 void visit(sp<fParamType> ) override;
		 void visit(sp<fParamTypes> ) override;
		 void visit(sp<fReturn> ) override;
		 void visit(sp<fStableId>) override;
		 void visit(sp<fTemplate>) override;
		 void visit(sp<fTemplateBody>) override;
		 void visit(sp<fThisFun>) override;
		 void visit(sp<fThrow>) override;
		 void visit(sp<fTraitDef>) override;
		 void visit(sp<fTry>) override;
		 void visit(sp<fType>) override;
		 void visit(sp<fTypeArgs>) override;
		 void visit(sp<fTypeDef>) override;
		 void visit(sp<fTypeParam>) override;
		 void visit(sp<fUnderscore>) override;
		 void visit(sp<fValue>) override;
		 void visit(sp<fValueDecl>) override;
		 void visit(sp<fValueDef>) override;
		 void visit(sp<fVariantTypeParam>) override;
		 void visit(sp<fWhile>) override;

	};
}
