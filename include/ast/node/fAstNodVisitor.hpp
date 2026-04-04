#pragma once

#include "fAstNod.hpp"

#include "fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"

// fIf and fTypeParamClause are forward-declared in the namespace block below;

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
	class fFunc;
	class fFunSig;
	class fFunTypeParamClause;
	class fGenerator;
	class fId;
	class fIds;
	class fIf;
	class fImport;
	class fLiteral;
	class fLocalModifier;
	class fModifier;
	class fModifiers;
	class fRegFunc;
	class fObjectDef;
	class fOverrideModifier;
	class fPackage;
	class fParam;
	class fParamClauses;
	class fParamType;
	class fParamTypes;
	class fReturn;
	class fStableId;
	class fSelfType;
	class fTemplate;
	class fTemplateBody;
	class fThisFunc;
	class fThrow;
	class fTraitDef;
	class fTry;
	class fType;
	class fTypeArgs;
	class fTypeDef;
	class fTypeParam;
	class fTypeParamClause;
	class fUnderscore;
	class fValueDcl;
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
		virtual void visit(sp<fAstOptrNod>, sbx)= 0;
		virtual void visit(sp<fAstOprndNod>, sbx) = 0;
		virtual void visit(sp<fAstProdSubTreeN>, sbx) = 0;

		// Leaf node visit methods

		virtual void visit(sp<fAccessModifier>, sbx) = 0;
		virtual void visit(sp<fAccessQualifier>, sbx) = 0;
		virtual void visit(sp<fBlock>, sbx) = 0;
		virtual void visit(sp<fCaseClause>, sbx) = 0;
		virtual void visit(sp<fCaseClauses>, sbx) = 0;
		virtual void visit(sp<fClassConstr>, sbx) = 0;
		virtual void visit(sp<fClassDef>, sbx) = 0;
		virtual void visit(sp<fClassParam>, sbx) = 0;
		virtual void visit(sp<fClassParamClauses>, sbx) = 0;
		virtual void visit(sp<fClassParents>, sbx) = 0;
		virtual void visit(sp<fClassTemplate>, sbx) = 0;
		virtual void visit(sp<fCompileUnit>, sbx) = 0;
		virtual void visit(sp<fConstrBlock>, sbx) = 0;
		virtual void visit(sp<fFor>, sbx) = 0;
		virtual void visit(sp<fFunc>, sbx) = 0;
		virtual void visit(sp<fFunSig>, sbx) = 0;
		virtual void visit(sp<fFunTypeParamClause>, sbx) = 0;;
		virtual void visit(sp<fGenerator>, sbx) = 0;
		virtual void visit(sp<fId>, sbx) = 0;
		virtual void visit(sp<fIds>, sbx) = 0;
		virtual void visit(sp<fIf>, sbx) = 0;
		virtual void visit(sp<fImport>, sbx) = 0;
		virtual void visit(sp<fLiteral>, sbx) = 0;
		virtual void visit(sp<fLocalModifier>, sbx) = 0;
		virtual void visit(sp<fModifier>, sbx) = 0;
		virtual void visit(sp<fModifiers>, sbx) = 0;
		virtual void visit(sp<fRegFunc>, sbx) = 0;
		virtual void visit(sp<fObjectDef>, sbx) = 0;
		virtual void visit(sp<fOverrideModifier>, sbx) = 0;
		virtual void visit(sp<fPackage>, sbx) = 0;
		virtual void visit(sp<fParam>, sbx) = 0;
		virtual void visit(sp<fParamClauses>, sbx) = 0;
		virtual void visit(sp<fParamType>, sbx) = 0;
		virtual void visit(sp<fParamTypes>, sbx) = 0;
		virtual void visit(sp<fReturn>, sbx) = 0;
		virtual void visit(sp<fStableId>, sbx) = 0;
		virtual void visit(sp<fSelfType>, sbx) = 0;
		virtual void visit(sp<fTemplate>, sbx) = 0;
		virtual void visit(sp<fTemplateBody>, sbx) = 0;
		virtual void visit(sp<fThisFunc>, sbx) = 0;
		virtual void visit(sp<fThrow>, sbx) = 0;
		virtual void visit(sp<fTraitDef>, sbx) = 0;
		virtual void visit(sp<fTry>, sbx) = 0;
		virtual void visit(sp<fType>, sbx) = 0;
		virtual void visit(sp<fTypeArgs>, sbx) = 0;
		virtual void visit(sp<fTypeDef>, sbx) = 0;
		virtual void visit(sp<fTypeParam>, sbx) = 0;
		virtual void visit(sp<fUnderscore>, sbx) = 0;
		virtual void visit(sp<fValueDcl>, sbx) = 0;
		virtual void visit(sp<fTypeParamClause> n, sbx)  = 0;
		virtual void visit(sp<fVariantTypeParam>, sbx) = 0;
		virtual void visit(sp<fWhile>, sbx) = 0;
	};
}
