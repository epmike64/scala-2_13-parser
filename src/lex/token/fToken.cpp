#include "lex/token/fToken.hpp"

#include <memory>

namespace zebra::lex::token {;

	const fToken  fToken::FILE_OFFSET(fTKnd::T_SOF, -1, -1, "<SOF>");
	const fToken  fToken::ROOT_OPERATOR(fTKnd::T_SOF, -1, -1, "<ROOT_OPERATOR>");
}