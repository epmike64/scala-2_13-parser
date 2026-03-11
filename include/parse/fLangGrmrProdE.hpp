#pragma once

#include <string>

namespace zebra::parse {

	enum class fLangGrmrProdE {
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
		BLOCK,
		COMPILATION_UNIT,
		POSTFIX_EXPR
  };

	// Utility function to convert enum to string
	inline std::string to_gr_prod_string(fLangGrmrProdE gp) {
		switch (gp) {
			case fLangGrmrProdE::EXPR: return "EXPR";
			case fLangGrmrProdE::EXPRS_OR_BINDINGS: return "EXPRS_OR_BINDINGS";
			case fLangGrmrProdE::SUBTREE: return "SUBTREE";
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
			case fLangGrmrProdE::BLOCK: return "BLOCK";
			case fLangGrmrProdE::COMPILATION_UNIT: return "COMPILATION_UNIT";
			case fLangGrmrProdE::POSTFIX_EXPR: return "POSTFIX_EXPR";
			default: return "UNKNOWN";
		}
	}

}