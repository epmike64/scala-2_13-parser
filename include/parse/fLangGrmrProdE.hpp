#pragma once

#include <string>

namespace zebra::parse {
	enum class fLangGrmrProdE {
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
	inline std::string to_gr_prod_string(fLangGrmrProdE gp) {
		switch (gp) {
			case fLangGrmrProdE::IF: return "IF";
			case fLangGrmrProdE::WHILE: return "WHILE";
			case fLangGrmrProdE::CASE_CLAUSE: return "CASE_CLAUSE";
			case fLangGrmrProdE::CLASS_CONSTR: return "CLASS_CONSTR";
			case fLangGrmrProdE::CLASS_PARAM: return "CLASS_PARAM";
			case fLangGrmrProdE::FOR: return "FOR";
			case fLangGrmrProdE::CONSTR_BLOCK: return "CONSTR_BLOCK";
			case fLangGrmrProdE::CASE_CLAUSES: return "CASE_CLAUSES";
			case fLangGrmrProdE::VALUE_DECL: return "VALUE_DECL";
			case fLangGrmrProdE::VALUE_DEF: return "VALUE_DEF";
			case fLangGrmrProdE::TYPE_DEF: return "TYPE_DEF";
			case fLangGrmrProdE::TYPE_ARGS: return "TYPE_ARGS";
			case fLangGrmrProdE::TRY: return "TRY";
			case fLangGrmrProdE::TRAIT_DEF: return "TRAIT_DEF";
			case fLangGrmrProdE::THIS_FUN: return "THIS_FUN";
			case fLangGrmrProdE::TEMPLATE: return "TEMPLATE";
			case fLangGrmrProdE::RETURN: return "RETURN";
			case fLangGrmrProdE::PARAM_CLAUSES: return "PARAM_CLAUSES";
			case fLangGrmrProdE::PARAM: return "PARAM";
			case fLangGrmrProdE::OBJECT: return "OBJECT";
			case fLangGrmrProdE::NAMED_FUN: return "NAMED_FUN";
			case fLangGrmrProdE::GENERATOR: return "GENERATOR";
			case fLangGrmrProdE::FUN_SIG: return "FUN_SIG";
			case fLangGrmrProdE::FFUN: return "FFUN";
			case fLangGrmrProdE::CLASS_PARENTS: return "CLASS_PARENTS";
			case fLangGrmrProdE::CLASS_PARAM_CLAUSES: return "CLASS_PARAM_CLAUSES";
			case fLangGrmrProdE::EXPR: return "EXPR";
			case fLangGrmrProdE::EXPRS_OR_BINDINGS: return "EXPRS_OR_BINDINGS";
			case fLangGrmrProdE::TYPES: return "TYPES";
			case fLangGrmrProdE::TYPE: return "TYPE";
			case fLangGrmrProdE::SIMPLE_TYPE: return "SIMPLE_TYPE";
			case fLangGrmrProdE::PARAM_TYPE: return "PARAM_TYPE";
			case fLangGrmrProdE::PARAM_TYPES: return "PARAM_TYPES";
			case fLangGrmrProdE::TYPE_ID: return "TYPE_ID";
			case fLangGrmrProdE::STABLE_ID: return "STABLE_ID";
			case fLangGrmrProdE::TEMPLATE_BODY: return "TEMPLATE_BODY";
			case fLangGrmrProdE::TEMPLATE_STAT: return "TEMPLATE_STAT";
			case fLangGrmrProdE::BLOCK_STAT: return "BLOCK_STAT";
			case fLangGrmrProdE::CLASS_TEMPLATE: return "CLASS_TEMPLATE";
			case fLangGrmrProdE::PATTERNS: return "PATTERNS";
			case fLangGrmrProdE::PATTERN: return "PATTERN";
			case fLangGrmrProdE::PATTERN_1: return "PATTERN_1";
			case fLangGrmrProdE::PATTERN_2: return "PATTERN_2";
			case fLangGrmrProdE::PATTERN_3: return "PATTERN_3";
			case fLangGrmrProdE::BLOCK: return "BLOCK";
			case fLangGrmrProdE::COMPILATION_UNIT: return "COMPILATION_UNIT";
			case fLangGrmrProdE::POSTFIX_EXPR: return "POSTFIX_EXPR";
			default: return "UNKNOWN";
		}
	}
}
