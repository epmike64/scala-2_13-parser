#pragma once

#include <string>
#include <unordered_map>
#include "lex/kind/fTTagE.hpp"


namespace zebra::lex::kind {

    class fTKnd {
    public:


        enum  fTKndE {
            T_SOF_E,
            T_EOF_E,
            T_ERROR_E,
            T_NL_E,
            T_ROOT_OPERATOR_E,
            T_CLASS_QUALIFIER_E,
            T_ID_E,
            T_INT_LIT_E,
            T_FLOAT_LIT_E,
            T_CHAR_LIT_E,
            T_STRING_LIT_E,
            T_ABSTRACT_E,
            T_CASE_E,
            T_CATCH_E,
            T_CLASS_E,
            T_DEF_E,
            T_DO_E,
            T_ELSE_E,
            T_EXTENDS_E,
            T_FALSE_E,
            T_FINALLY_E,
            T_FINAL_E,
            T_FOR_E,
            T_IF_E,
            T_IMPLICIT_E,
            T_IMPORT_E,
            T_LAZY_E,
            T_MATCH_E,
            T_NEW_E,
            T_NULL_E,
            T_OBJECT_E,
            T_OVERRIDE_E,
            T_PACKAGE_E,
            T_PRIVATE_E,
            T_PROTECTED_E,
            T_RETURN_E,
            T_SEALED_E,
            T_SUPER_E,
            T_THIS_E,
            T_THROW_E,
            T_TRAIT_E,
            T_TRUE_E,
            T_TRY_E,
            T_TYPE_E,
            T_VAL_E,
            T_VAR_E,
            T_WHILE_E,
            T_WITH_E,
            T_YIELD_E,
            T_EQUAL_E,
            T_NOT_EQUAL_E,
            T_LOGICAL_AND_E,
            T_LOGICAL_OR_E,
            T_ASSIGN_E,
            T_ASSIGN_PLUS_E,
            T_ASSIGN_MINUS_E,
            T_ASSIGN_MULTIPLY_E,
            T_ASSIGN_DIVIDE_E,
            T_ASSIGN_MODULO_E,
            T_EXCLAMATION_E,
            T_POUND_E,
            T_PERCENT_E,
            T_AMPERSAND_E,
            T_AT_E,
            T_PIPE_E,
            T_COLON_E,
            T_TILDE_E,
            T_PLUS_E,
            T_MINUS_E,
            T_STAR_E,
            T_FORWARD_SLASH_E,
            T_LT_E,
            T_LTE_E,
            T_GT_E,
            T_GTE_E,
            T_CARET_E,
            T_QUESTION_E,
            T_UNDERSCORE_E,
            T_FAT_ARROW_E,
            T_IN_E,
            T_DOT_E,
            T_COMMA_E,
            T_SEMICOLON_E,
            T_UPPER_BOUND_E,
            T_LOWER_BOUND_E,
            T_LCURL_E,
            T_RCURL_E,
            T_LPAREN_E,
            T_RPAREN_E,
            T_LBRACKET_E,
            T_RBRACKET_E,
            T_CONTEXT_BOUND_E
        };

        static const fTKnd* const  T_SOF;
        static const fTKnd*  const T_EOF;
        static const fTKnd* const  T_ERROR;
        static const fTKnd* const  T_NL;
        static const fTKnd* const  T_ROOT_OPERATOR;

        static const fTKnd* const  T_CLASS_QUALIFIER;
        static const fTKnd* const  T_ID;
        static const fTKnd* const  T_INT_LIT;
        static const fTKnd* const  T_FLOAT_LIT;
        static const fTKnd* const  T_CHAR_LIT;
        static const fTKnd* const  T_STRING_LIT;

        static const fTKnd* const  T_ABSTRACT;
        static const fTKnd* const  T_CASE;
        static const fTKnd* const  T_CATCH;
        static const fTKnd* const  T_CLASS;
        static const fTKnd* const  T_DEF;
        static const fTKnd* const  T_DO;
        static const fTKnd* const  T_ELSE;
        static const fTKnd* const  T_EXTENDS;
        static const fTKnd* const  T_FALSE;
        static const fTKnd* const  T_FINALLY;
        static const fTKnd* const  T_FINAL;
        static const fTKnd* const  T_FOR;
        static const fTKnd* const  T_IF;
        static const fTKnd* const  T_IMPLICIT;
        static const fTKnd* const  T_IMPORT;
        static const fTKnd* const  T_LAZY;
        static const fTKnd* const  T_MATCH;
        static const fTKnd* const  T_NEW;
        static const fTKnd* const  T_NULL;
        static const fTKnd* const  T_OBJECT;
        static const fTKnd* const  T_OVERRIDE;
        static const fTKnd* const  T_PACKAGE;
        static const fTKnd* const  T_PRIVATE;
        static const fTKnd* const  T_PROTECTED;
        static const fTKnd* const  T_RETURN;
        static const fTKnd* const  T_SEALED;
        static const fTKnd* const  T_SUPER;
        static const fTKnd* const  T_THIS;
        static const fTKnd* const  T_THROW;
        static const fTKnd* const  T_TRAIT;
        static const fTKnd* const  T_TRUE;
        static const fTKnd* const  T_TRY;
        static const fTKnd* const  T_TYPE;
        static const fTKnd* const  T_VAL;
        static const fTKnd* const  T_VAR;
        static const fTKnd* const  T_WHILE;
        static const fTKnd* const  T_WITH;
        static const fTKnd* const  T_YIELD;

        static const fTKnd* const  T_EQUAL;
        static const fTKnd* const  T_NOT_EQUAL;
        static const fTKnd* const  T_LOGICAL_AND;
        static const fTKnd* const  T_LOGICAL_OR;
        static const fTKnd* const  T_ASSIGN;
        static const fTKnd* const  T_EXCLAMATION;
        static const fTKnd* const  T_POUND;
        static const fTKnd* const  T_PERCENT;
        static const fTKnd* const  T_AMPERSAND;
        static const fTKnd* const  T_AT;
        static const fTKnd* const  T_PIPE;
        static const fTKnd* const  T_COLON;
        static const fTKnd* const  T_TILDE;
        static const fTKnd* const  T_PLUS;
        static const fTKnd* const  T_MINUS;
        static const fTKnd* const  T_STAR;
        static const fTKnd* const  T_FORWARD_SLASH;
        static const fTKnd* const  T_LT;
        static const fTKnd* const  T_LTE;
        static const fTKnd* const  T_GT;
        static const fTKnd* const  T_GTE;
        static const fTKnd* const  T_CARET;
        static const fTKnd* const  T_QUESTION;
        static const fTKnd* const  T_UNDERSCORE;
        static const fTKnd* const  T_FAT_ARROW;
        static const fTKnd* const  T_IN;
        static const fTKnd* const  T_DOT;
        static const fTKnd* const  T_COMMA;
        static const fTKnd* const  T_SEMICOLON;
        static const fTKnd* const  T_UPPER_BOUND;
        static const fTKnd* const  T_LOWER_BOUND;
        static const fTKnd* const  T_LCURL;
        static const fTKnd* const  T_RCURL;
        static const fTKnd* const  T_LPAREN;
        static const fTKnd* const  T_RPAREN;
        static const fTKnd* const  T_LBRACKET;
        static const fTKnd* const  T_RBRACKET;
        static const fTKnd* const  T_CONTEXT_BOUND;

        // Static method to get token by name
        static const fTKnd* findByName(const std::string& name);
        fTTagE tag() const { return _tTag; }

        // CRITICAL: Implicit conversion to Value for switch statements
        constexpr operator fTKndE() const { return _tkE; }

        // Prevent accidental conversion to bool
        explicit operator bool() = delete;

        // Accessors
        constexpr fTKndE value() const { return _tkE; }
        const std::string& name() const { return _tkName; }


        // Comparison operators (value-based)
        constexpr bool operator==(const fTKnd& other) const {
            return _tkE == other._tkE;
        }
        constexpr bool operator!=(const fTKnd& other) const {
            return _tkE != other._tkE;
        }

        // Comparison operators (pointer-based identity)
        bool operator==(const fTKnd* other) const {
            return this == other;
        }
        bool operator!=(const fTKnd* other) const {
            return this != other;
        }

        // Value-based comparison
        constexpr bool operator==(fTKndE other) const {
            return _tkE == other;
        }
        constexpr bool operator!=(fTKndE other) const {
            return _tkE != other;
        }

        // String representation
        friend std::ostream& operator<<(std::ostream& os, const fTKnd& kind) {
            return os << kind._tkName;
        }
        friend std::ostream& operator<<(std::ostream& os, const fTKnd* kind) {
            return os << (kind ? kind->_tkName : "null");
        }

        fTTagE getTTag() const {
            return _tTag;
        }

        fTKndE getTkEnumVal() const {
            return _tkE;
        }

        const std::string& getTkName() const {
            return _tkName;
        }

        const std::string toString() const;

    private:
        fTKnd(const std::string &name, const fTTagE tag, fTKndE val);

        fTKnd(const fTKnd& other) = delete;

        fTKnd& operator=(const fTKnd& other) = delete;

        fTKnd(fTKnd&& other)  = delete;

        fTKnd& operator=(fTKnd&& other)= delete;

        ~fTKnd() = default;

        const fTKndE _tkE;
    	const std::string _tkName;
    	const fTTagE _tTag;

        static const fTKnd* createInstance(std::string&& tkName,  fTTagE tag, fTKndE val);


        static std::unordered_map<std::string, const fTKnd *> & getInstanceMap();
    };
}