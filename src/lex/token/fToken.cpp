#include "lex/token/fToken.hpp"

#include <memory>

namespace zebra::lex::token {;

	const fToken  fToken::FILE_OFFSET(fTKnd::T_SOF, -1, -1, "<SOF>");
	const fToken  fToken::ROOT_OPERATOR(fTKnd::T_SOF, -1, -1, "<ROOT_OPERATOR>");

	fToken::fToken(const fTKnd*  kind,  int pos, int endPos, const std::string& tsval):
			pos_(pos), endPos_(endPos), kind_(kind), strVal_(tsval) {
	}

	const std::string& fToken::getTStrVal() const {
		return strVal_;
	}
	const fTKnd* fToken::getTKind() const {
		return kind_;
	}

	int fToken::radix() const {
		throw std::runtime_error("UnsupportedOperationException: radix() not supported for this token type");
	}

	std::string fToken::toString() const {
		std::ostringstream oss;
		oss << "fToken{kind=" << (kind_ ? kind_->toString() : "null")
			<< ", pos=" << pos_
			<< ", endPos=" << endPos_
			<< ", strVal='" << strVal_ << "'}";
		return oss.str();
	}
}