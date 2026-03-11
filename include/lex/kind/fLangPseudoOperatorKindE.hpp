#pragma once
#include "lex/token/fToken.hpp"

namespace zebra::lex::kind {

	enum class fLangPseudoOperatorKindE {
		O_ID,
		O_COLON,
		O_DOT,
		O_COMMA,
		O_ETA_EXPANSION,
		O_WITH,
		O_FAT_ARROW,
		O_BRACKETS,
		O_CURLY_BRACES,
		O_AT,
		O_PIPE,
		O_PARENS
	};

	class fLangPseudoOperator {
	public:
		static bool isTokenAsID_RightAssociative(const token::fToken* token);
	};

}
