#pragma once

#include "fModifier.hpp"
#include "../symbol/ZEnclScope.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	enum fLangOprndType {
		ACCESS_MODIFIER,
		ACCESS_QUALIFIER,
		BLOCK,
		CASE_CLAUSE,
		CASE_CLAUSES,
		CLASS_CONSTR,
		CLASS_DEF,
		CLASS_PARAM,
		CLASS_PARAM_CLAUSES,
		CLASS_PARENTS,
		CLASS_TEMPLATE,
		COMPILE_UNIT,
		CONSTR_BLOCK,
		FOR, FUNC, FUNC_SIG, FUN_TYPE_PARAM_CLAUSE,
		GENERATOR, ID, IDS, IF, IMPORT, LITERAL, LOCAL_MODIFIER,
		MODIFIER, MODIFIERS, OBJECT_DEF,  OVERRIDE_MODIFIER,
		PACKAGE, PARAM, PARAM_CLAUSES, PARAM_TYPE, PARAM_TYPES,
		REG_FUNC, RETURN, STABLE_ID, TEMPLATE, TEMPLATE_BODY, THIS, TRAIT_DEF,
		TYPE, TYPE_DEF, TYPE_PARAM, TYPE_PARAM_CLAUSE, VALUE_DCL, WHILE, TYPE_ARGS,
		 VARIANT_TYPE_PARAM, VARIANT_TYPE_PARAM_CLAUSE,

	};

	class fLangOprnd: public fAstOprndNod {
	public:
		fLangOprnd();
		virtual ~fLangOprnd();
		virtual fLangOprndType getLangOprndType() = 0;
	};

}