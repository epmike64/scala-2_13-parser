#pragma once

#include <string>
#include <stdexcept>
#include "fTKnd.hpp"
#include "lex/token/fToken.hpp"

namespace zebra::lex::kind {
	using lex::token::fToken;


	class fLangOperatorKind {
	public:

		enum class fLangOptrE {

			O_PSEUDO_E,

			// Postfix
			O_BRACKETS_E,
			O_PARENS_E,

			// Unary
			O_TILDA_E,
			O_EXCLAMATION_E,

			// Multiplicative
			O_MULTIPLY_E,
			O_DIVIDE_E,
			O_MODULO_E,

			// Additive
			O_PLUS_E,
			O_MINUS_E,

			// Relational
			O_LESS_E,
			O_LESS_EQUAL_E,
			O_GREATER_E,
			O_GREATER_EQUAL_E,

			// Equality
			O_EQUAL_E,
			O_NOT_EQUAL_E,

			// Logical
			O_LOGICAL_AND_E,
			O_LOGICAL_OR_E,

			// Assignment
			O_ASSIGN_MULTIPLY_E,
			O_ASSIGN_DIVIDE_E,
			O_ASSIGN_MODULO_E,
			O_ASSIGN_MINUS_E,
			O_ASSIGN_PLUS_E,
			O_ASSIGN_E,

			// Comma
			O_COMMA_E,

			// Internal root operator (not exposed to source code)
			O_INTERN_ROOT_E
		};

		// Postfix
		static const fLangOperatorKind *const O_BRACKETS;
		static const fLangOperatorKind *const O_PARENS;

		// Unary operators
		static const fLangOperatorKind *const O_TILDA;
		static const fLangOperatorKind *const O_EXCLAMATION;

		// Multiplicative operators
		static const fLangOperatorKind *const O_MULTIPLY;
		static const fLangOperatorKind *const O_DIVIDE;
		static const fLangOperatorKind *const O_MODULO;

		// Additive operators
		static const fLangOperatorKind *const O_PLUS;
		static const fLangOperatorKind *const O_MINUS;

		// Relational operators
		static const fLangOperatorKind *const O_LESS;
		static const fLangOperatorKind *const O_LESS_EQUAL;
		static const fLangOperatorKind *const O_GREATER;
		static const fLangOperatorKind *const O_GREATER_EQUAL;


		// Equality operators
		static const fLangOperatorKind *const O_EQUAL;
		static const fLangOperatorKind *const O_NOT_EQUAL;

		// Logical operators
		static const fLangOperatorKind *const O_LOGICAL_AND;
		static const fLangOperatorKind *const O_LOGICAL_OR;

		// Assignment operators
		static const fLangOperatorKind *const O_ASSIGN;
		static const fLangOperatorKind *const O_ASSIGN_MINUS;
		static const fLangOperatorKind *const O_ASSIGN_PLUS;
		static const fLangOperatorKind *const O_ASSIGN_MULTIPLY;
		static const fLangOperatorKind *const O_ASSIGN_DIVIDE;
		static const fLangOperatorKind *const O_ASSIGN_MODULO;

		// Comma
		static const fLangOperatorKind *const O_COMMA;

		// AST Build Help: Pseudo-operator
		static const fLangOperatorKind *const O_PSEUDO;
		// AST Build Help: root operator
		static const fLangOperatorKind *const O_INTERN_ROOT;

		// Public interface
		const std::string &getOpname() const { return _operName; }
		bool isRightAssociative() const { return _isOperRightAssoc; }

		int precedence() const {
			return _operPrecedence;
		}

		// Static factory methods
		static const fLangOperatorKind *getIdSymbolicAssoc(bool isRightAssociative);

		static const fLangOperatorKind *getLogicalOperatorKind(const fTKnd *kind);

		static const fLangOperatorKind *getRelationalOptrKind(const fTKnd *kind);

		static const fLangOperatorKind *getMathOptrKnd(const fTKnd *kind);

		// Get instance by name (for the static map functionality)
		static const fLangOperatorKind *findByName(const std::string &name);

		// CRITICAL: Implicit conversion to Value for switch statements
		constexpr operator fLangOptrE() const { return _valE; }

		// Prevent accidental conversion to bool
		explicit operator bool() = delete;

		// Accessors
		constexpr fLangOptrE value() const { return _valE; }

		// Comparison operators (value-based)
		constexpr bool operator==(const fLangOperatorKind& other) const {
			return _valE == other._valE;
		}
		constexpr bool operator!=(const fLangOperatorKind& other) const {
			return _valE != other._valE;
		}

		// Comparison operators (pointer-based identity)
		bool operator==(const fLangOperatorKind* other) const {
			return this == other;
		}
		bool operator!=(const fLangOperatorKind* other) const {
			return this != other;
		}

		// Value-based comparison
		constexpr bool operator==(fLangOptrE other) const {
			return _valE == other;
		}
		constexpr bool operator!=(fLangOptrE other) const {
			return _valE != other;
		}

		static const fLangOperatorKind* const getOptrKnd(const fToken* token);

		std::string getOperName(const fToken* token);
		 std::string toString() const {
			 return "fLangOperatorKind(" + _operName + ", precedence=" + std::to_string(_operPrecedence) +
				 ", rightAssociative=" + (_isOperRightAssoc ? "true" : "false") + ")";
		 }

		static const fLangOperatorKind* getLangOptr(const fTKnd* kind);

	private:
		fLangOperatorKind(const std::string &opname, int precedence, bool isRightAssociative, fLangOptrE v, bool isBinary);

		fLangOperatorKind(const fLangOperatorKind &) = delete;

		fLangOperatorKind &operator=(const fLangOperatorKind &) = delete;

		fLangOperatorKind(fLangOperatorKind &&) = delete;

		fLangOperatorKind &operator=(fLangOperatorKind &&) = delete;

		~fLangOperatorKind() = default;


		const fLangOptrE _valE;
		const std::string _operName;
		const int _operPrecedence;
		const bool _isOperRightAssoc;
		const bool _isBinary;

		static const fLangOperatorKind *createInstance(std::string&& opname,
		                                               int precedence,
		                                               bool isRightAssociative, fLangOptrE v, bool isBinary);


		static std::unordered_map<std::string, const fLangOperatorKind *>  & getInstanceMap();


	};
}
