#pragma once

#include "fAstNod.hpp"
#include "fAstNodKndE.hpp"
#include <memory>

#include "EnclsScope.hpp"
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
		virtual void visit(sp<fAstOptrNod>, EnclsScope) = 0;
		virtual void visit(sp<fAstOprndNod>, EnclsScope)  = 0;
		virtual void visit(sp<fAstProdSubTreeN>, EnclsScope)  = 0;

		// Leaf node visit methods

		virtual void visit(sp<fAccessModifier>, EnclsScope)  = 0;
		virtual void visit(sp<fAccessQualifier>, EnclsScope)  = 0;
		virtual void visit(sp<fBlock>, EnclsScope)  = 0;
		virtual void visit(sp<fCaseClause>, EnclsScope)  = 0;
		virtual void visit(sp<fCaseClauses>, EnclsScope)  = 0;
		virtual void visit(sp<fClassConstr>, EnclsScope)  = 0;
		virtual void visit(sp<fClassDef>, EnclsScope)  = 0;
		virtual void visit(sp<fClassParam>, EnclsScope)  = 0;
		virtual void visit(sp<fClassParamClauses>, EnclsScope)  = 0;
		virtual void visit(sp<fClassParents>, EnclsScope)  = 0;
		virtual void visit(sp<fClassTemplate>, EnclsScope)  = 0;
		virtual void visit(sp<fCompileUnit>, EnclsScope)  = 0;
		virtual void visit(sp<fConstrBlock>, EnclsScope)  = 0;
		virtual void visit(sp<fFor>, EnclsScope)  = 0;
		virtual void visit(sp<fFun>, EnclsScope)  = 0;
		virtual void visit(sp<fFunSig>, EnclsScope)  = 0;
		virtual void visit(sp<fGenerator>, EnclsScope)  = 0;
		virtual void visit(sp<fId>, EnclsScope)  = 0;
		virtual void visit(sp<fIds>, EnclsScope)  = 0;
		virtual void visit(sp<fIf>, EnclsScope)  = 0;
		virtual void visit(sp<fImport>, EnclsScope)  = 0;
		virtual void visit(sp<fLiteral>, EnclsScope)  = 0;
		virtual void visit(sp<fLocalModifier>, EnclsScope)  = 0;
		virtual void visit(sp<fModifier>, EnclsScope)  = 0;
		virtual void visit(sp<fModifiers>, EnclsScope)  = 0;
		virtual void visit(sp<fNamedFun>, EnclsScope)  = 0;
		virtual void visit(sp<fObject>, EnclsScope)  = 0;
		virtual void visit(sp<fOverrideModifier>, EnclsScope)  = 0;
		virtual void visit(sp<fPackage>, EnclsScope)  = 0;
		virtual void visit(sp<fParam>, EnclsScope)  = 0;
		virtual void visit(sp<fParamClauses>, EnclsScope)  = 0;
		virtual void visit(sp<fParamType>, EnclsScope)  = 0;
		virtual void visit(sp<fParamTypes>, EnclsScope)  = 0;
		virtual void visit(sp<fReturn>, EnclsScope)  = 0;
		virtual void visit(sp<fStableId>, EnclsScope)  = 0;
		virtual void visit(sp<fTemplate>, EnclsScope)  = 0;
		virtual void visit(sp<fTemplateBody>, EnclsScope)  = 0;
		virtual void visit(sp<fThisFun>, EnclsScope)  = 0;
		virtual void visit(sp<fThrow>, EnclsScope)  = 0;
		virtual void visit(sp<fTraitDef>, EnclsScope)  = 0;
		virtual void visit(sp<fTry>, EnclsScope)  = 0;
		virtual void visit(sp<fType>, EnclsScope)  = 0;
		virtual void visit(sp<fTypeArgs>, EnclsScope)  = 0;
		virtual void visit(sp<fTypeDef>, EnclsScope)  = 0;
		virtual void visit(sp<fTypeParam>, EnclsScope)  = 0;
		virtual void visit(sp<fUnderscore>, EnclsScope)  = 0;
		virtual void visit(sp<fValue>, EnclsScope)  = 0;
		virtual void visit(sp<fValueDecl>, EnclsScope)  = 0;
		virtual void visit(sp<fValueDef>, EnclsScope)  = 0;
		virtual void visit(sp<fVariantTypeParam>, EnclsScope)  = 0;
		virtual void visit(sp<fWhile>, EnclsScope)  = 0;
	};
}
