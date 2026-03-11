#pragma once

#include "token/fToken.hpp"

namespace zebra::lex {

	using token::fToken;

	class fLexerIFace {
	public:
		virtual ~fLexerIFace() = default;
		virtual const fToken* nextToken() = 0;
		virtual const fToken* lookAhead(int n) = 0;
		virtual bool currentAtEof() const = 0;
		virtual bool filledToEof() const = 0;
	};
}
