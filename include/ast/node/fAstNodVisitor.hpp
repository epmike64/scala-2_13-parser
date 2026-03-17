#pragma once

#include "fAstNod.hpp"


#include "fAstProdSubTreeN.hpp"
#include "ast/leaf/fIf.hpp"
#include "ast/leaf/fTypeParamClause.hpp"
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
	class fTypeParamClause;
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
	using namespace ast::symbol;

	class fAstNodVisitor {
	public:
		~fAstNodVisitor() = default;
		virtual  void visit() = 0; // Entry point for visiting the AST
		virtual void visit(sp<fAstOptrNod>, esc)= 0;
		virtual void visit(sp<fAstOprndNod>, esc) = 0;
		virtual void visit(sp<fAstProdSubTreeN>, esc) = 0;

		// Leaf node visit methods

		virtual void visit(sp<fAccessModifier>, esc) = 0;
		virtual void visit(sp<fAccessQualifier>, esc) = 0;
		virtual void visit(sp<fBlock>, esc) = 0;
		virtual void visit(sp<fCaseClause>, esc) = 0;
		virtual void visit(sp<fCaseClauses>, esc) = 0;
		virtual void visit(sp<fClassConstr>, esc) = 0;
		virtual void visit(sp<fClassDef>, esc) = 0;
		virtual void visit(sp<fClassParam>, esc) = 0;
		virtual void visit(sp<fClassParamClauses>, esc) = 0;
		virtual void visit(sp<fClassParents>, esc) = 0;
		virtual void visit(sp<fClassTemplate>, esc) = 0;
		virtual void visit(sp<fCompileUnit>, esc) = 0;
		virtual void visit(sp<fConstrBlock>, esc) = 0;
		virtual void visit(sp<fFor>, esc) = 0;
		virtual void visit(sp<fFun>, esc) = 0;
		virtual void visit(sp<fFunSig>, esc) = 0;
		virtual void visit(sp<fGenerator>, esc) = 0;
		virtual void visit(sp<fId>, esc) = 0;
		virtual void visit(sp<fIds>, esc) = 0;
		virtual void visit(sp<fIf>, esc) = 0;
		virtual void visit(sp<fImport>, esc) = 0;
		virtual void visit(sp<fLiteral>, esc) = 0;
		virtual void visit(sp<fLocalModifier>, esc) = 0;
		virtual void visit(sp<fModifier>, esc) = 0;
		virtual void visit(sp<fModifiers>, esc) = 0;
		virtual void visit(sp<fNamedFun>, esc) = 0;
		virtual void visit(sp<fObject>, esc) = 0;
		virtual void visit(sp<fOverrideModifier>, esc) = 0;
		virtual void visit(sp<fPackage>, esc) = 0;
		virtual void visit(sp<fParam>, esc) = 0;
		virtual void visit(sp<fParamClauses>, esc) = 0;
		virtual void visit(sp<fParamType>, esc) = 0;
		virtual void visit(sp<fParamTypes>, esc) = 0;
		virtual void visit(sp<fReturn>, esc) = 0;
		virtual void visit(sp<fStableId>, esc) = 0;
		virtual void visit(sp<fTemplate>, esc) = 0;
		virtual void visit(sp<fTemplateBody>, esc) = 0;
		virtual void visit(sp<fThisFun>, esc) = 0;
		virtual void visit(sp<fThrow>, esc) = 0;
		virtual void visit(sp<fTraitDef>, esc) = 0;
		virtual void visit(sp<fTry>, esc) = 0;
		virtual void visit(sp<fType>, esc) = 0;
		virtual void visit(sp<fTypeArgs>, esc) = 0;
		virtual void visit(sp<fTypeDef>, esc) = 0;
		virtual void visit(sp<fTypeParam>, esc) = 0;
		virtual void visit(sp<fUnderscore>, esc) = 0;
		virtual void visit(sp<fValue>, esc) = 0;
		virtual void visit(sp<fValueDecl>, esc) = 0;
		virtual void visit(sp<fValueDef>, esc) = 0;
		virtual void visit(sp<fTypeParamClause> n, esc)  = 0;
		virtual void visit(sp<fVariantTypeParam>, esc) = 0;
		virtual void visit(sp<fWhile>, esc) = 0;
	};
}
