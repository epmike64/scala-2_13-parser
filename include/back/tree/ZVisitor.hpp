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
#include "ast/leaf/fAnnotation.hpp"
#include "ast/leaf/fAnnotations.hpp"
#include "ast/leaf/fClassConstr.hpp"
#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fFunc.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fImport.hpp"
#include "ast/leaf/fModifier.hpp"
#include "ast/leaf/fPackage.hpp"
#include "ast/leaf/fParamType.hpp"
#include "ast/leaf/fSelfType.hpp"
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
		sp<ZProgram> zProgram_;

	public:
		explicit ZVisitor(sp<fCompileUnit> cu) : compileUnit_(cu) {
		}

		void visit() override;
		void visit(sp<fCompileUnit>, sbx) override;
		//
		void visit(sp<fAstOptrNod>, sbx) override;
		void visit(sp<fAstOprndNod>, sbx) override;
		void visit(sp<fAstProdSubTreeN>, sbx) override;
		//-- Leaf node visit methods
		void visit(sp<fAccessModifier>, sbx) override;
		void visit(sp<fAccessQualifier>, sbx) override;
		void visit(sp<fAnnotation>, sbx) override;
		void visit(sp<fAnnotations>, sbx) override;
		void visit(sp<fBlock>, sbx) override;
		void visit(sp<fCaseClause>, sbx) override;
		void visit(sp<fCaseClauses>, sbx) override;
		void visit(sp<fClassConstr>, sbx) override;
		void visit(sp<fClassDef>, sbx) override;
		void visit(sp<fClassParam>, sbx) override;
		void visit(sp<fClassParamClauses>, sbx) override;
		void visit(sp<fClassParents>, sbx) override;
		void visit(sp<fClassTemplate>, sbx) override;
		void visit(sp<fConstrBlock>, sbx) override;
		void visit(sp<fFor>, sbx) override;
		void visit(sp<fFunc>, sbx) override;
		void visit(sp<fFunSig>, sbx) override;
		void visit(sp<fFunTypeParamClause>, sbx) override;
		void visit(sp<fGenerator>, sbx) override;
		void visit(sp<fId>, sbx) override;
		void visit(sp<fIds>, sbx) override;
		void visit(sp<fIf>, sbx) override;
		void visit(sp<fImport>, sbx) override;
		void visit(sp<fLiteral>, sbx) override;
		void visit(sp<fLocalModifier>, sbx) override;
		void visit(sp<fModifier>, sbx) override;
		void visit(sp<fModifiers>, sbx) override;
		void visit(sp<fRegFunc>, sbx) override;
		void visit(sp<fObjectDef>, sbx) override;
		void visit(sp<fOverrideModifier>, sbx) override;
		void visit(sp<fPackage>, sbx) override;
		void visit(sp<fParam>, sbx) override;
		void visit(sp<fParamClauses>, sbx) override;
		void visit(sp<fParamType>, sbx) override;
		void visit(sp<fParamTypes>, sbx) override;
		void visit(sp<fReturn>, sbx) override;
		void visit(sp<fStableId>, sbx) override;
		void visit(sp<fSelfType>, sbx) override;
		void visit(sp<fTemplate>, sbx) override;
		void visit(sp<fTemplateBody>, sbx) override;
		void visit(sp<fThisFunc>, sbx) override;
		void visit(sp<fThrow>, sbx) override;
		void visit(sp<fTraitDef>, sbx) override;
		void visit(sp<fTry>, sbx) override;
		void visit(sp<fType>, sbx) override;
		void visit(sp<fTypeArgs>, sbx) override;
		void visit(sp<fTypeDef>, sbx) override;
		void visit(sp<fTypeParam>, sbx) override;
		void visit(sp<fUnderscore>, sbx) override;
		void visit(sp<fValueDcl>, sbx) override;
		void visit(sp<fTypeParamClause> n, sbx) override;
		void visit(sp<fVariantTypeParam>, sbx) override;
		void visit(sp<fVarargsExpansion> n, sbx prnSbx) override;
		void visit(sp<fWhile>, sbx) override;

		sp<ZProgram> getZProgram() {
			return zProgram_;
		}
	};
}
