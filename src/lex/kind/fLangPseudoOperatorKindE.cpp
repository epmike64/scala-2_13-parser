#include "lex/kind/fLangPseudoOperatorKindE.hpp"

namespace zebra::lex::kind {

	bool fLangPseudoOperator::isTokenAsID_RightAssociative(const token::fToken* token) {
		std::string name = token->getTStrVal();
		if (name.size() < 2) throw std::invalid_argument(name);
		if (name.at(name.size() - 1) == ':') return true;
		return false;
	}
}
