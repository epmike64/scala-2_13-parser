#include <cassert>
#include <memory>
#include <unordered_map>

#include "lex/kind/fLangOperatorKind.hpp"

#include "lex/util/fLangMethNameCheck.hpp"

namespace zebra::ast::node::leaves::lex::token::type {
	class fToken;
}

namespace zebra::lex::kind {
	// Private constructor
	fLangOperatorKind::fLangOperatorKind(const std::string &opname, int precedence, bool isRightAssociative, fLangOptrE val, bool isBinary)
		: _operName(opname), _operPrecedence(precedence), _isOperRightAssoc(isRightAssociative), _valE(val), _isBinary(isBinary) {
		assert(!opname.empty() && "opname must not be empty");
	}

	// Static factory method
	const fLangOperatorKind *fLangOperatorKind::createInstance(std::string&& opname,
	                                                           int precedence,
	                                                           bool isRightAssociative, fLangOptrE v, bool isBinary) {
		const fLangOperatorKind *kind = new fLangOperatorKind(std::move(opname), precedence, isRightAssociative, v, isBinary);
		getInstanceMap()[kind->_operName] = kind;
		return kind;
	}

	// Static map accessor
	std::unordered_map<std::string, const fLangOperatorKind *> &fLangOperatorKind::getInstanceMap() {
		static std::unordered_map<std::string, const fLangOperatorKind *> instanceMap;
		return instanceMap;
	}

	using enum fLangOperatorKind::fLangOptrE;

	//--- 9 Postfix

	const fLangOperatorKind *const fLangOperatorKind::O_BRACKETS = createInstance("[]", 10, false,  O_BRACKETS_E, false);
	const fLangOperatorKind *const fLangOperatorKind::O_PARENS = createInstance("()", 10, false, O_PARENS_E, false);


	//---- 8 Unary
	const fLangOperatorKind *const fLangOperatorKind::O_EXCLAMATION = createInstance("!", 9, true, O_EXCLAMATION_E, false);
	const fLangOperatorKind *const fLangOperatorKind::O_TILDA = createInstance("~", 9, true, O_TILDA_E, false);

	//---- 7 Multiplicative

	const fLangOperatorKind *const fLangOperatorKind::O_MULTIPLY = createInstance("*", 8, false, O_MULTIPLY_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_DIVIDE = createInstance("/", 8, false, O_DIVIDE_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_MODULO = createInstance("%", 8, false, O_MODULO_E, true);

	//--- 6 Additive

	const fLangOperatorKind *const fLangOperatorKind::O_PLUS = createInstance("+", 7, false, O_PLUS_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_MINUS = createInstance("-", 7, false, O_MINUS_E, true);

	//---- 5 Relational

	const fLangOperatorKind *const fLangOperatorKind::O_LESS = createInstance("<", 6, false, O_LESS_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_LESS_EQUAL = createInstance("<=", 6, false, O_LESS_EQUAL_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_GREATER = createInstance(">", 6, false, O_GREATER_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_GREATER_EQUAL = createInstance(">=", 6, false, O_GREATER_EQUAL_E, true);

	//---- 4 Equality

	const fLangOperatorKind *const fLangOperatorKind::O_EQUAL = createInstance("==", 5, false,O_EQUAL_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_NOT_EQUAL = createInstance("!=", 5, false, O_NOT_EQUAL_E, true);


	//---- 3 Logical AND

	const fLangOperatorKind *const fLangOperatorKind::O_LOGICAL_AND = createInstance("&&", 4, false, O_LOGICAL_AND_E, true);

	// --- 3 Logical OR

	const fLangOperatorKind *const fLangOperatorKind::O_LOGICAL_OR = createInstance("||", 3, false, O_LOGICAL_OR_E, true);

	//---- 2 Assignment

	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN = createInstance("=", 2, false, O_ASSIGN_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN_PLUS = createInstance("=+", 2, false, O_ASSIGN_PLUS_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN_MINUS = createInstance("=-", 2, false, O_ASSIGN_MINUS_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN_MODULO = createInstance("=%", 2, false, O_ASSIGN_MODULO_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN_MULTIPLY = createInstance("=*", 2, false, O_ASSIGN_MULTIPLY_E, true);
	const fLangOperatorKind *const fLangOperatorKind::O_ASSIGN_DIVIDE = createInstance("=/", 2, false, O_ASSIGN_DIVIDE_E, true);

	//---- 1 Comma

	const fLangOperatorKind *const fLangOperatorKind::O_COMMA = createInstance(",", 1, false, O_COMMA_E, true);


	//---- AST Build: language pseudo operator
	const fLangOperatorKind *const fLangOperatorKind::O_PSEUDO = createInstance("\x01\x01", -99, false,  O_PSEUDO_E, false);

	// -- AST Build: root operator
	const fLangOperatorKind *const fLangOperatorKind::O_INTERN_ROOT = createInstance("\x01", -100, false, O_INTERN_ROOT_E, true);

	const fLangOperatorKind* fLangOperatorKind::getLangOptr(const fTKnd* kind) {
		switch (*kind) {

			// Postfix
			case fTKnd::T_LPAREN_E:
				return O_PARENS;
			case fTKnd::T_LBRACKET_E:
				return O_BRACKETS;

				// Unary
			case fTKnd::T_EXCLAMATION_E:
				return O_EXCLAMATION;
			case fTKnd::T_TILDE_E:
				return O_TILDA;

				// Multiplicative
			case fTKnd::T_STAR_E:
				return O_MULTIPLY;
			case fTKnd::T_FORWARD_SLASH_E:
				return O_DIVIDE;
			case fTKnd::T_PERCENT_E:
				return O_MODULO;

				// Additive
			case fTKnd::T_PLUS_E:
				return O_PLUS;
			case fTKnd::T_MINUS_E:
				return O_MINUS;


				// Relational
			case fTKnd::T_LT_E:
				return O_LESS;
			case fTKnd::T_LTE_E:
				return O_LESS_EQUAL;
			case fTKnd::T_GT_E:
				return O_GREATER;
			case fTKnd::T_GTE_E:
				return O_GREATER_EQUAL;

			// Equality
			case fTKnd::T_EQUAL_E:
				return O_EQUAL;
			case fTKnd::T_NOT_EQUAL_E:
				return O_NOT_EQUAL;

			// Logical
			case fTKnd::T_LOGICAL_AND_E:
				return O_LOGICAL_AND;
			case fTKnd::T_LOGICAL_OR_E:
				return O_LOGICAL_OR;

			// Assignment
			case fTKnd::T_ASSIGN_E:
				return O_ASSIGN;
			case fTKnd::T_ASSIGN_PLUS_E:
				return O_ASSIGN_PLUS;
			case fTKnd::T_ASSIGN_MINUS_E:
				return O_ASSIGN_MINUS;
			case fTKnd::T_ASSIGN_MULTIPLY_E:
				return O_ASSIGN_MULTIPLY;
			case fTKnd::T_ASSIGN_DIVIDE_E:
				return O_ASSIGN_DIVIDE;
			case fTKnd::T_ASSIGN_MODULO_E:
				return O_ASSIGN_MODULO;

				// Comma
			case fTKnd::T_COMMA_E:
				return O_COMMA;

			default:
				throw std::invalid_argument("Token kind does not correspond to a known operator");
		}
	}
}
// namespace flint::lex::token
