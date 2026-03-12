#include "lex/kind/fTKnd.hpp"

namespace zebra::lex::kind {
	using namespace zebra::lex::kind;



	fTKnd::fTKnd(const std::string &name, const fTTagE tag, fTKndE val) : _tkName(name), _tTag(tag), _tkE(val) {}

	const fTKnd* fTKnd::createInstance(std::string&& tkName, fTTagE tag, fTKndE v) {
		const fTKnd* kind =  new fTKnd(std::move(tkName), tag, v);
		getInstanceMap()[kind->_tkName] = kind;
		return kind;
	}

	std::unordered_map<std::string, const fTKnd *> & fTKnd::getInstanceMap(){
		static std::unordered_map<std::string, const fTKnd *> instanceMap;
		return instanceMap;
	}

	using enum fTKnd::fTKndE;

	const fTKnd *const fTKnd::T_SOF = createInstance("_T_SOF", fTTagE::INTERN, T_SOF_E);
	const fTKnd *const fTKnd::T_EOF = createInstance("_T_EOF", fTTagE::INTERN, T_EOF_E);
	const fTKnd *const fTKnd::T_ERROR = createInstance("_T_ERROR", fTTagE::INTERN, T_ERROR_E);
	const fTKnd *const fTKnd::T_NL = createInstance("_T_NL", fTTagE::INTERN, T_NL_E);
	const fTKnd *const fTKnd::T_ROOT_OPERATOR = createInstance("_T_ROOT_OPER", fTTagE::INTERN, T_ROOT_OPERATOR_E);

	const fTKnd *const fTKnd::T_CLASS_QUALIFIER = createInstance("_T_CLASS_QLF", fTTagE::NAME_VAL, T_CLASS_QUALIFIER_E);
	const fTKnd *const fTKnd::T_ID = createInstance("_T_ID", fTTagE::NAME_VAL, T_ID_E);
	const fTKnd *const fTKnd::T_INT_LIT = createInstance("_T_INT_LIT", fTTagE::NUMERIC, T_INT_LIT_E);
	const fTKnd *const fTKnd::T_FLOAT_LIT = createInstance("_T_FLOAT_LIT", fTTagE::NUMERIC, T_FLOAT_LIT_E);
	const fTKnd *const fTKnd::T_CHAR_LIT = createInstance("_T_CHAR_LIT", fTTagE::NUMERIC, T_CHAR_LIT_E);
	const fTKnd *const fTKnd::T_STRING_LIT = createInstance("_T_STRING_LIT", fTTagE::STRING, T_STRING_LIT_E);

	const fTKnd *const fTKnd::T_ABSTRACT = createInstance("abstract", fTTagE::KEYWORD, T_ABSTRACT_E);
	const fTKnd *const fTKnd::T_CASE = createInstance("case", fTTagE::KEYWORD, T_CASE_E);
	const fTKnd *const fTKnd::T_CATCH = createInstance("catch", fTTagE::KEYWORD, T_CATCH_E);
	const fTKnd *const fTKnd::T_CLASS = createInstance("class", fTTagE::KEYWORD, T_CLASS_E);
	const fTKnd *const fTKnd::T_DEF = createInstance("def", fTTagE::KEYWORD, T_DEF_E);
	const fTKnd *const fTKnd::T_DO = createInstance("do", fTTagE::KEYWORD, T_DO_E);
	const fTKnd *const fTKnd::T_ELSE = createInstance("else", fTTagE::KEYWORD, T_ELSE_E);
	const fTKnd *const fTKnd::T_EXTENDS = createInstance("extends", fTTagE::KEYWORD, T_EXTENDS_E);
	const fTKnd *const fTKnd::T_FALSE = createInstance("false", fTTagE::KEYWORD, T_FALSE_E);
	const fTKnd *const fTKnd::T_FINALLY = createInstance("finally", fTTagE::KEYWORD, T_FINALLY_E);
	const fTKnd *const fTKnd::T_FINAL = createInstance("final", fTTagE::KEYWORD, T_FINAL_E);
	const fTKnd *const fTKnd::T_FOR = createInstance("for", fTTagE::KEYWORD, T_FOR_E);
	const fTKnd *const fTKnd::T_IF = createInstance("if", fTTagE::KEYWORD, T_IF_E);
	const fTKnd *const fTKnd::T_IMPLICIT = createInstance("implicit", fTTagE::KEYWORD, T_IMPLICIT_E);
	const fTKnd *const fTKnd::T_IMPORT = createInstance("import", fTTagE::KEYWORD, T_IMPORT_E);
	const fTKnd *const fTKnd::T_LAZY = createInstance("lazy", fTTagE::KEYWORD, T_LAZY_E);
	const fTKnd *const fTKnd::T_MATCH = createInstance("match", fTTagE::KEYWORD, T_MATCH_E);
	const fTKnd *const fTKnd::T_NEW = createInstance("new", fTTagE::KEYWORD, T_NEW_E);
	const fTKnd *const fTKnd::T_NULL = createInstance("null", fTTagE::KEYWORD, T_NULL_E);
	const fTKnd *const fTKnd::T_OBJECT = createInstance("object", fTTagE::KEYWORD, T_OBJECT_E);
	const fTKnd *const fTKnd::T_OVERRIDE = createInstance("override", fTTagE::KEYWORD, T_OVERRIDE_E);
	const fTKnd *const fTKnd::T_PACKAGE = createInstance("package", fTTagE::KEYWORD, T_PACKAGE_E);
	const fTKnd *const fTKnd::T_PRIVATE = createInstance("private", fTTagE::KEYWORD, T_PRIVATE_E);
	const fTKnd *const fTKnd::T_PROTECTED = createInstance("protected", fTTagE::KEYWORD, T_PROTECTED_E);
	const fTKnd *const fTKnd::T_RETURN = createInstance("return", fTTagE::KEYWORD, T_RETURN_E);
	const fTKnd *const fTKnd::T_SEALED = createInstance("sealed", fTTagE::KEYWORD, T_SEALED_E);
	const fTKnd *const fTKnd::T_SUPER = createInstance("super", fTTagE::KEYWORD, T_SUPER_E);
	const fTKnd *const fTKnd::T_THIS = createInstance("this", fTTagE::KEYWORD, T_THIS_E);
	const fTKnd *const fTKnd::T_THROW = createInstance("throw", fTTagE::KEYWORD, T_THROW_E);
	const fTKnd *const fTKnd::T_TRAIT = createInstance("trait", fTTagE::KEYWORD, T_TRAIT_E);
	const fTKnd *const fTKnd::T_TRUE = createInstance("true", fTTagE::KEYWORD, T_TRUE_E);
	const fTKnd *const fTKnd::T_TRY = createInstance("try", fTTagE::KEYWORD, T_TRY_E);
	const fTKnd *const fTKnd::T_TYPE = createInstance("type", fTTagE::KEYWORD, T_TYPE_E);
	const fTKnd *const fTKnd::T_VAL = createInstance("val", fTTagE::KEYWORD, T_VAL_E);
	const fTKnd *const fTKnd::T_VAR = createInstance("var", fTTagE::KEYWORD, T_VAR_E);
	const fTKnd *const fTKnd::T_WHILE = createInstance("while", fTTagE::KEYWORD, T_WHILE_E);
	const fTKnd *const fTKnd::T_WITH = createInstance("with", fTTagE::KEYWORD, T_WITH_E);
	const fTKnd *const fTKnd::T_YIELD = createInstance("yield", fTTagE::KEYWORD, T_YIELD_E);

	const fTKnd *const fTKnd::T_EQUAL = createInstance("==", fTTagE::OPERATOR, T_EQUAL_E);
	const fTKnd *const fTKnd::T_NOT_EQUAL = createInstance("!=", fTTagE::OPERATOR, T_NOT_EQUAL_E);
	const fTKnd *const fTKnd::T_LOGICAL_AND = createInstance("&&", fTTagE::OPERATOR, T_LOGICAL_AND_E);
	const fTKnd *const fTKnd::T_LOGICAL_OR = createInstance("||", fTTagE::OPERATOR, T_LOGICAL_OR_E);
	const fTKnd *const fTKnd::T_ASSIGN = createInstance("=", fTTagE::OPERATOR, T_ASSIGN_E);
	const fTKnd *const fTKnd::T_EXCLAMATION = createInstance("!", fTTagE::OPERATOR, T_EXCLAMATION_E);
	const fTKnd *const fTKnd::T_POUND = createInstance("#", fTTagE::OPERATOR, T_POUND_E);
	const fTKnd *const fTKnd::T_PERCENT = createInstance("%", fTTagE::OPERATOR, T_PERCENT_E);
	const fTKnd *const fTKnd::T_AMPERSAND = createInstance("&", fTTagE::OPERATOR, T_AMPERSAND_E);
	const fTKnd *const fTKnd::T_AT = createInstance("@", fTTagE::OPERATOR, T_AT_E);
	const fTKnd *const fTKnd::T_PIPE = createInstance("|", fTTagE::OPERATOR, T_PIPE_E);
	const fTKnd *const fTKnd::T_COLON = createInstance(":", fTTagE::OPERATOR, T_COLON_E);
	const fTKnd *const fTKnd::T_TILDE = createInstance("~", fTTagE::OPERATOR, T_TILDE_E);
	const fTKnd *const fTKnd::T_PLUS = createInstance("+", fTTagE::OPERATOR, T_PLUS_E);
	const fTKnd *const fTKnd::T_MINUS = createInstance("-", fTTagE::OPERATOR, T_MINUS_E);
	const fTKnd *const fTKnd::T_STAR = createInstance("*", fTTagE::OPERATOR, T_STAR_E);
	const fTKnd *const fTKnd::T_FORWARD_SLASH = createInstance("/", fTTagE::OPERATOR, T_FORWARD_SLASH_E);
	const fTKnd *const fTKnd::T_LT = createInstance("<", fTTagE::OPERATOR, T_LT_E);
	const fTKnd *const fTKnd::T_LTE = createInstance("<=", fTTagE::OPERATOR, T_LTE_E);
	const fTKnd *const fTKnd::T_GT = createInstance(">", fTTagE::OPERATOR, T_GT_E);
	const fTKnd *const fTKnd::T_GTE = createInstance(">=", fTTagE::OPERATOR, T_GTE_E);
	const fTKnd *const fTKnd::T_CARET = createInstance("^", fTTagE::OPERATOR, T_CARET_E);
	const fTKnd *const fTKnd::T_QUESTION = createInstance("?", fTTagE::OPERATOR, T_QUESTION_E);
	const fTKnd *const fTKnd::T_UNDERSCORE = createInstance("_", fTTagE::UNDERSCORE, T_UNDERSCORE_E);
	const fTKnd *const fTKnd::T_FAT_ARROW = createInstance("=>", fTTagE::OPERATOR, T_FAT_ARROW_E);
	const fTKnd *const fTKnd::T_IN = createInstance("<-", fTTagE::OPERATOR, T_IN_E);
	const fTKnd *const fTKnd::T_DOT = createInstance(".", fTTagE::OPERATOR, T_DOT_E);
	const fTKnd *const fTKnd::T_COMMA = createInstance(",", fTTagE::OPERATOR, T_COMMA_E);
	const fTKnd *const fTKnd::T_SEMICOLON = createInstance(";", fTTagE::OPERATOR, T_SEMICOLON_E);
	const fTKnd *const fTKnd::T_UPPER_BOUND = createInstance("<:", fTTagE::OPERATOR, T_UPPER_BOUND_E);
	const fTKnd *const fTKnd::T_LOWER_BOUND = createInstance(">:", fTTagE::OPERATOR, T_LOWER_BOUND_E);
	const fTKnd *const fTKnd::T_LCURL = createInstance("{", fTTagE::OPERATOR, T_LCURL_E);
	const fTKnd *const fTKnd::T_RCURL = createInstance("}", fTTagE::OPERATOR, T_RCURL_E);
	const fTKnd *const fTKnd::T_LPAREN = createInstance("(", fTTagE::OPERATOR, T_LPAREN_E);
	const fTKnd *const fTKnd::T_RPAREN = createInstance(")", fTTagE::OPERATOR, T_RPAREN_E);
	const fTKnd *const fTKnd::T_LBRACKET = createInstance("[", fTTagE::OPERATOR, T_LBRACKET_E);
	const fTKnd *const fTKnd::T_RBRACKET = createInstance("]", fTTagE::OPERATOR, T_RBRACKET_E);
	const fTKnd *const fTKnd::T_CONTEXT_BOUND = createInstance("<%", fTTagE::OPERATOR, T_CONTEXT_BOUND_E);



	// Method to get token by name
	const fTKnd *fTKnd::findByName(const std::string &name) {
		const auto &map = getInstanceMap();
		const auto it = map.find(name);
		return it != map.end() ? it->second : T_ID;
	}

	const std::string fTKnd::toString() const  {
		std::string tkNameS = _tkName;
		if (_tTag == fTTagE::OPERATOR || _tTag == fTTagE::KEYWORD) {
			tkNameS = "\'" + tkNameS + "\'";
		}

		return "fTKnd{kind=" + tkNameS
					+ ", tag=" + fTTagE_Tostring(_tTag)
					+ "}";
	}
}

