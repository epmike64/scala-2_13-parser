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
		virtual void visit(sp<fAstOptrNod>, ssc)= 0;
		virtual void visit(sp<fAstOprndNod>, ssc) = 0;
		virtual void visit(sp<fAstProdSubTreeN>, ssc) = 0;

		// Leaf node visit methods

		virtual void visit(sp<fAccessModifier>, ssc) = 0;
		virtual void visit(sp<fAccessQualifier>, ssc) = 0;
		virtual void visit(sp<fBlock>, ssc) = 0;
		virtual void visit(sp<fCaseClause>, ssc) = 0;
		virtual void visit(sp<fCaseClauses>, ssc) = 0;
		virtual void visit(sp<fClassConstr>, ssc) = 0;
		virtual void visit(sp<fClassDef>, ssc) = 0;
		virtual void visit(sp<fClassParam>, ssc) = 0;
		virtual void visit(sp<fClassParamClauses>, ssc) = 0;
		virtual void visit(sp<fClassParents>, ssc) = 0;
		virtual void visit(sp<fClassTemplate>, ssc) = 0;
		virtual void visit(sp<fCompileUnit>, ssc) = 0;
		virtual void visit(sp<fConstrBlock>, ssc) = 0;
		virtual void visit(sp<fFor>, ssc) = 0;
		virtual void visit(sp<fFunc>, ssc) = 0;
		virtual void visit(sp<fFunSig>, ssc) = 0;
		virtual void visit(sp<fFunTypeParamClause>, ssc) = 0;;
		virtual void visit(sp<fGenerator>, ssc) = 0;
		virtual void visit(sp<fId>, ssc) = 0;
		virtual void visit(sp<fIds>, ssc) = 0;
		virtual void visit(sp<fIf>, ssc) = 0;
		virtual void visit(sp<fImport>, ssc) = 0;
		virtual void visit(sp<fLiteral>, ssc) = 0;
		virtual void visit(sp<fLocalModifier>, ssc) = 0;
		virtual void visit(sp<fModifier>, ssc) = 0;
		virtual void visit(sp<fModifiers>, ssc) = 0;
		virtual void visit(sp<fRegFunc>, ssc) = 0;
		virtual void visit(sp<fObjectDef>, ssc) = 0;
		virtual void visit(sp<fOverrideModifier>, ssc) = 0;
		virtual void visit(sp<fPackage>, ssc) = 0;
		virtual void visit(sp<fParam>, ssc) = 0;
		virtual void visit(sp<fParamClauses>, ssc) = 0;
		virtual void visit(sp<fParamType>, ssc) = 0;
		virtual void visit(sp<fParamTypes>, ssc) = 0;
		virtual void visit(sp<fReturn>, ssc) = 0;
		virtual void visit(sp<fStableId>, ssc) = 0;
		virtual void visit(sp<fTemplate>, ssc) = 0;
		virtual void visit(sp<fTemplateBody>, ssc) = 0;
		virtual void visit(sp<fThisFunc>, ssc) = 0;
		virtual void visit(sp<fThrow>, ssc) = 0;
		virtual void visit(sp<fTraitDef>, ssc) = 0;
		virtual void visit(sp<fTry>, ssc) = 0;
		virtual void visit(sp<fType>, ssc) = 0;
		virtual void visit(sp<fTypeArgs>, ssc) = 0;
		virtual void visit(sp<fTypeDef>, ssc) = 0;
		virtual void visit(sp<fTypeParam>, ssc) = 0;
		virtual void visit(sp<fUnderscore>, ssc) = 0;
		virtual void visit(sp<fValueDcl>, ssc) = 0;
		virtual void visit(sp<fTypeParamClause> n, ssc)  = 0;
		virtual void visit(sp<fVariantTypeParam>, ssc) = 0;
		virtual void visit(sp<fWhile>, ssc) = 0;
	};
}
