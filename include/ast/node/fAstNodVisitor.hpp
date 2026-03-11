#pragma once

#include "fAstNod.hpp"
#include "fAstNodKndE.hpp"
#include <memory>

#include "fAstProdSubTreeN.hpp"
#include "ast/leaf/fIf.hpp"
#include "util/fCommon.hpp"

// Forward declarations only — leaf headers include fAstNod.hpp which would
namespace zebra::ast::leaf {
	class fAccessModifier;
	class fAccessQualifier;
	class fBlock;
	class fCaseClause;
	class fCaseClauses;
	class fClassConstr;
	class fClassDef;
	class fClassParam;
	class fClassParamClauses;
	class fClassParents;
	class fClassTemplate;
	class fCompileUnit;
	class fConstrBlock;
	class fFor;
	class fFun;
	class fFunSig;
	class fGenerator;
	class fId;
	class fIds;
	class fIf;
	class fImport;
	class fLiteral;
	class fLocalModifier;
	class fModifier;
	class fModifiers;
	class fNamedFun;
	class fObject;
	class fOverrideModifier;
	class fPackage;
	class fParam;
	class fParamClauses;
	class fParamType;
	class fParamTypes;
	class fReturn;
	class fStableId;
	class fTemplate;
	class fTemplateBody;
	class fThisFun;
	class fThrow;
	class fTraitDef;
	class fTry;
	class fType;
	class fTypeArgs;
	class fTypeDef;
	class fTypeParam;
	class fUnderscore;
	class fValue;
	class fValueDecl;
	class fValueDef;
	class fVariantTypeParam;
	class fWhile;
}

// create circular includes if pulled in here.

namespace zebra::ast::node {
	class fAstOptrNod;
	class fAstOprndNod;
}

namespace zebra::ast::node {

	using namespace ast::leaf;
	using namespace ast::node;
	using namespace util;

	class fAstNodVisitor {
	public:
		~fAstNodVisitor() = default;

		virtual  void visit() = 0; // Entry point for visiting the AST
		virtual void visit(sp<fAstOptrNod>) = 0;
		virtual void visit(sp<fAstOprndNod>) = 0;
		virtual void visit(sp<fAstProdSubTreeN> ) = 0;

		// Leaf node visit methods

		virtual void visit(sp<fAccessModifier> ) = 0;
		virtual void visit(sp<fAccessQualifier> ) = 0;
		virtual void visit(sp<fBlock> ) = 0;
		virtual void visit(sp<fCaseClause> ) = 0;
		virtual void visit(sp<fCaseClauses> ) = 0;
		virtual void visit(sp<fClassConstr> ) = 0;
		virtual void visit(sp<fClassDef>) = 0;
		virtual void visit(sp<fClassParam>) = 0;
		virtual void visit(sp<fClassParamClauses>) = 0;
		virtual void visit(sp<fClassParents>) = 0;
		virtual void visit(sp<fClassTemplate>) = 0;
		virtual void visit(sp<fCompileUnit>) = 0;
		virtual void visit(sp<fConstrBlock>) = 0;
		virtual void visit(sp<fFor>) = 0;
		virtual void visit(sp<fFun>) = 0;
		virtual void visit(sp<fFunSig>) = 0;
		virtual void visit(sp<fGenerator>) = 0;
		virtual void visit(sp<fId>) = 0;
		virtual void visit(sp<fIds>) = 0;
		virtual void visit(sp<fIf>) = 0;
		virtual void visit(sp<fImport>) = 0;
		virtual void visit(sp<fLiteral>) = 0;
		virtual void visit(sp<fLocalModifier>) = 0;
		virtual void visit(sp<fModifier>) = 0;
		virtual void visit(sp<fModifiers>) = 0;
		virtual void visit(sp<fNamedFun>) = 0;
		virtual void visit(sp<fObject>) = 0;
		virtual void visit(sp<fOverrideModifier>) = 0;
		virtual void visit(sp<fPackage>) = 0;
		virtual void visit(sp<fParam> ) = 0;
		virtual void visit(sp<fParamClauses> ) = 0;
		virtual void visit(sp<fParamType> ) = 0;
		virtual void visit(sp<fParamTypes> ) = 0;
		virtual void visit(sp<fReturn> ) = 0;
		virtual void visit(sp<fStableId>) = 0;
		virtual void visit(sp<fTemplate>) = 0;
		virtual void visit(sp<fTemplateBody>) = 0;
		virtual void visit(sp<fThisFun>) = 0;
		virtual void visit(sp<fThrow>) = 0;
		virtual void visit(sp<fTraitDef>) = 0;
		virtual void visit(sp<fTry>) = 0;
		virtual void visit(sp<fType>) = 0;
		virtual void visit(sp<fTypeArgs>) = 0;
		virtual void visit(sp<fTypeDef>) = 0;
		virtual void visit(sp<fTypeParam>) = 0;
		virtual void visit(sp<fUnderscore>) = 0;
		virtual void visit(sp<fValue>) = 0;
		virtual void visit(sp<fValueDecl>) = 0;
		virtual void visit(sp<fValueDef>) = 0;
		virtual void visit(sp<fVariantTypeParam>) = 0;
		virtual void visit(sp<fWhile>) = 0;
	};
}
