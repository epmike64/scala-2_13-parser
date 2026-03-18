#pragma once

#include <string>

namespace zebra::parse {
	enum class ZGrmrProdE {
		IF,
		WHILE,
		CASE_CLAUSE,
		CASE_CLAUSES,
		TYPE_PARAM_CLAUSE,
		VALUE_DECL, VALUE_DEF,TYPE_DEF, TYPE_ARGS, TRY, TRAIT_DEF, THIS_FUN, TEMPLATE, RETURN, PARAM_CLAUSES,
		PARAM, OBJECT, NAMED_FUN, GENERATOR, FUN_SIG, FFUN, CONSTR_BLOCK, CLASS_CONSTR, CLASS_PARAM,
		FOR, CLASS_PARENTS, CLASS_PARAM_CLAUSES,
		EXPR,
		EXPRS_OR_BINDINGS,
		SUBTREE,
		TYPES,
		TYPE,
		SIMPLE_TYPE,
		PARAM_TYPE,
		PARAM_TYPES,
		TYPE_ID,
		STABLE_ID,
		TEMPLATE_BODY,
		TEMPLATE_STAT,
		BLOCK_STAT,
		CLASS_TEMPLATE,
		PATTERNS,
		PATTERN,
		PATTERN_1,
		PATTERN_2,
		PATTERN_3,
		BLOCK,
		COMPILATION_UNIT,
		POSTFIX_EXPR
	};

	// Utility function to convert enum to string
	inline std::string to_gr_prod_string(ZGrmrProdE gp) {
		switch (gp) {
			case ZGrmrProdE::IF: return "IF";
			case ZGrmrProdE::WHILE: return "WHILE";
			case ZGrmrProdE::CASE_CLAUSE: return "CASE_CLAUSE";
			case ZGrmrProdE::CLASS_CONSTR: return "CLASS_CONSTR";
			case ZGrmrProdE::CLASS_PARAM: return "CLASS_PARAM";
			case ZGrmrProdE::FOR: return "FOR";
			case ZGrmrProdE::CONSTR_BLOCK: return "CONSTR_BLOCK";
			case ZGrmrProdE::CASE_CLAUSES: return "CASE_CLAUSES";
			case ZGrmrProdE::VALUE_DECL: return "VALUE_DECL";
			case ZGrmrProdE::VALUE_DEF: return "VALUE_DEF";
			case ZGrmrProdE::TYPE_DEF: return "TYPE_DEF";
			case ZGrmrProdE::TYPE_ARGS: return "TYPE_ARGS";
			case ZGrmrProdE::TRY: return "TRY";
			case ZGrmrProdE::TRAIT_DEF: return "TRAIT_DEF";
			case ZGrmrProdE::THIS_FUN: return "THIS_FUN";
			case ZGrmrProdE::TEMPLATE: return "TEMPLATE";
			case ZGrmrProdE::RETURN: return "RETURN";
			case ZGrmrProdE::PARAM_CLAUSES: return "PARAM_CLAUSES";
			case ZGrmrProdE::PARAM: return "PARAM";
			case ZGrmrProdE::OBJECT: return "OBJECT";
			case ZGrmrProdE::NAMED_FUN: return "NAMED_FUN";
			case ZGrmrProdE::GENERATOR: return "GENERATOR";
			case ZGrmrProdE::FUN_SIG: return "FUN_SIG";
			case ZGrmrProdE::FFUN: return "FFUN";
			case ZGrmrProdE::CLASS_PARENTS: return "CLASS_PARENTS";
			case ZGrmrProdE::CLASS_PARAM_CLAUSES: return "CLASS_PARAM_CLAUSES";
			case ZGrmrProdE::EXPR: return "EXPR";
			case ZGrmrProdE::EXPRS_OR_BINDINGS: return "EXPRS_OR_BINDINGS";
			case ZGrmrProdE::SUBTREE: return "SUBTREE";
			case ZGrmrProdE::TYPES: return "TYPES";
			case ZGrmrProdE::TYPE: return "TYPE";
			case ZGrmrProdE::SIMPLE_TYPE: return "SIMPLE_TYPE";
			case ZGrmrProdE::PARAM_TYPE: return "PARAM_TYPE";
			case ZGrmrProdE::PARAM_TYPES: return "PARAM_TYPES";
			case ZGrmrProdE::TYPE_ID: return "TYPE_ID";
			case ZGrmrProdE::STABLE_ID: return "STABLE_ID";
			case ZGrmrProdE::TEMPLATE_BODY: return "TEMPLATE_BODY";
			case ZGrmrProdE::TEMPLATE_STAT: return "TEMPLATE_STAT";
			case ZGrmrProdE::BLOCK_STAT: return "BLOCK_STAT";
			case ZGrmrProdE::CLASS_TEMPLATE: return "CLASS_TEMPLATE";
			case ZGrmrProdE::PATTERNS: return "PATTERNS";
			case ZGrmrProdE::PATTERN: return "PATTERN";
			case ZGrmrProdE::PATTERN_1: return "PATTERN_1";
			case ZGrmrProdE::PATTERN_2: return "PATTERN_2";
			case ZGrmrProdE::PATTERN_3: return "PATTERN_3";
			case ZGrmrProdE::BLOCK: return "BLOCK";
			case ZGrmrProdE::COMPILATION_UNIT: return "COMPILATION_UNIT";
			case ZGrmrProdE::POSTFIX_EXPR: return "POSTFIX_EXPR";
			default: return "UNKNOWN";
		}
	}
}
