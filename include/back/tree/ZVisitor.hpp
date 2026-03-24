
#pragma once

#include "ast/node/fAstNod.hpp"

#include <memory>

#include "ast/node/fAstNodVisitor.hpp"
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
#include "ast/leaf/fFunc.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fImport.hpp"
#include "ast/leaf/fModifier.hpp"
#include "ast/leaf/fPackage.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fTypeArgs.hpp"
#include "ast/symbol/ZSymbol.hpp"

namespace zebra::back::tree {

	using namespace ast::node;
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	class ZVisitor : public fAstNodVisitor, public std::enable_shared_from_this<ZVisitor> {
	protected:
		sp<fCompileUnit> compileUnit_;
		sp<fAstNod> getAstPSTreeRightN(sp<fAstProdSubTreeN> subTree);

	public:
		explicit ZVisitor(sp<fCompileUnit> cu) : compileUnit_(cu){}
		void visit() override;
		void visit(sp<fCompileUnit>, esc) override;
		//
		void visit(sp<fAstOptrNod>, esc) override;
		void visit(sp<fAstOprndNod>, esc) override;
		void visit(sp<fAstProdSubTreeN>, esc) override;
		//-- Leaf node visit methods
		void visit(sp<fAccessModifier>, esc) override;
		 void visit(sp<fAccessQualifier>, esc) override;
		 void visit(sp<fBlock>, esc) override;
		 void visit(sp<fCaseClause>, esc) override;
		 void visit(sp<fCaseClauses>, esc) override;
		 void visit(sp<fClassConstr>, esc) override;
		 void visit(sp<fClassDef>, esc) override;
		 void visit(sp<fClassParam>, esc) override;
		 void visit(sp<fClassParamClauses>, esc) override;
		 void visit(sp<fClassParents>, esc) override;
		 void visit(sp<fClassTemplate>, esc) override;
		 void visit(sp<fConstrBlock>, esc) override;
		 void visit(sp<fFor>, esc) override;
		 void visit(sp<fFunc>, esc) override;
		 void visit(sp<fFunSig>, esc) override;
		 void visit(sp<fFunTypeParamClause>, esc) override;
		 void visit(sp<fGenerator>, esc) override;
		 void visit(sp<fId>, esc) override;
		 void visit(sp<fIds>, esc) override;
		 void visit(sp<fIf>, esc) override;
		 void visit(sp<fImport>, esc) override;
		 void visit(sp<fLiteral>, esc) override;
		 void visit(sp<fLocalModifier>, esc) override;
		 void visit(sp<fModifier>, esc) override;
		 void visit(sp<fModifiers>, esc) override;
		 void visit(sp<fRegFunc>, esc) override;
		 void visit(sp<fObjectDef>, esc) override;
		 void visit(sp<fOverrideModifier>, esc) override;
		 void visit(sp<fPackage>, esc) override;
		 void visit(sp<fParam>, esc) override;
		 void visit(sp<fParamClauses>, esc) override;
		 void visit(sp<fParamType>, esc) override;
		 void visit(sp<fParamTypes>, esc) override;
		 void visit(sp<fReturn>, esc) override;
		 void visit(sp<fStableId>, esc) override;

		void visit(sp<fTemplate>, esc) override;
		 void visit(sp<fTemplateBody>, esc) override;
		 void visit(sp<fThisFunc>, esc) override;
		 void visit(sp<fThrow>, esc) override;
		 void visit(sp<fTraitDef>, esc) override;
		 void visit(sp<fTry>, esc) override;
		 void visit(sp<fType>, esc) override;
		 void visit(sp<fTypeArgs>, esc) override;
		 void visit(sp<fTypeDef>, esc) override;
		 void visit(sp<fTypeParam>, esc) override;
		 void visit(sp<fUnderscore>, esc) override;
		 void visit(sp<fValue>, esc) override;
		 void visit(sp<fValueDecl>, esc) override;
		void visit(sp<fTypeParamClause> n, esc) override;
		void visit(sp<fValueDef>, esc) override;
		 void visit(sp<fVariantTypeParam>, esc) override;
		 void visit(sp<fWhile>, esc) override;

	private:
		sp<ZProdSubTreeN> visitIntoSubTree(sp<fAstNod> node, esc prnSc);
	};
}
