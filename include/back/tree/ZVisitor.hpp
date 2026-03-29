
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
		void visit(sp<fCompileUnit>, ssc) override;
		//
		void visit(sp<fAstOptrNod>, ssc) override;
		void visit(sp<fAstOprndNod>, ssc) override;
		void visit(sp<fAstProdSubTreeN>, ssc) override;
		//-- Leaf node visit methods
		void visit(sp<fAccessModifier>, ssc) override;
		 void visit(sp<fAccessQualifier>, ssc) override;
		 void visit(sp<fBlock>, ssc) override;
		 void visit(sp<fCaseClause>, ssc) override;
		 void visit(sp<fCaseClauses>, ssc) override;
		 void visit(sp<fClassConstr>, ssc) override;
		 void visit(sp<fClassDef>, ssc) override;
		 void visit(sp<fClassParam>, ssc) override;
		 void visit(sp<fClassParamClauses>, ssc) override;
		 void visit(sp<fClassParents>, ssc) override;
		 void visit(sp<fClassTemplate>, ssc) override;
		 void visit(sp<fConstrBlock>, ssc) override;
		 void visit(sp<fFor>, ssc) override;
		 void visit(sp<fFunc>, ssc) override;
		 void visit(sp<fFunSig>, ssc) override;
		 void visit(sp<fFunTypeParamClause>, ssc) override;
		 void visit(sp<fGenerator>, ssc) override;
		 void visit(sp<fId>, ssc) override;
		 void visit(sp<fIds>, ssc) override;
		 void visit(sp<fIf>, ssc) override;
		 void visit(sp<fImport>, ssc) override;
		 void visit(sp<fLiteral>, ssc) override;
		 void visit(sp<fLocalModifier>, ssc) override;
		 void visit(sp<fModifier>, ssc) override;
		 void visit(sp<fModifiers>, ssc) override;
		 void visit(sp<fRegFunc>, ssc) override;
		 void visit(sp<fObjectDef>, ssc) override;
		 void visit(sp<fOverrideModifier>, ssc) override;
		 void visit(sp<fPackage>, ssc) override;
		 void visit(sp<fParam>, ssc) override;
		 void visit(sp<fParamClauses>, ssc) override;
		 void visit(sp<fParamType>, ssc) override;
		 void visit(sp<fParamTypes>, ssc) override;
		 void visit(sp<fReturn>, ssc) override;
		 void visit(sp<fStableId>, ssc) override;

		void visit(sp<fTemplate>, ssc) override;
		 void visit(sp<fTemplateBody>, ssc) override;
		 void visit(sp<fThisFunc>, ssc) override;
		 void visit(sp<fThrow>, ssc) override;
		 void visit(sp<fTraitDef>, ssc) override;
		 void visit(sp<fTry>, ssc) override;
		 void visit(sp<fType>, ssc) override;
		 void visit(sp<fTypeArgs>, ssc) override;
		 void visit(sp<fTypeDef>, ssc) override;
		 void visit(sp<fTypeParam>, ssc) override;
		 void visit(sp<fUnderscore>, ssc) override;
		 void visit(sp<fValueDcl>, ssc) override;
		void visit(sp<fTypeParamClause> n, ssc) override;
		 void visit(sp<fVariantTypeParam>, ssc) override;
		 void visit(sp<fWhile>, ssc) override;
	};
}
