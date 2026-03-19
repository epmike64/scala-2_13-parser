#include "lex/token/fToken.hpp"

#include <memory>

namespace zebra::lex::token {;

	const fToken  fToken::FILE_OFFSET(fTKnd::T_SOF, -1, -1, -1, -1,"<SOF>");
	const fToken  fToken::ROOT_OPERATOR(fTKnd::T_SOF, -1, -1, -1, -1,"<ROOT_OPERATOR>");

	fToken::fToken(const fTKnd*  kind,  int pos, int endPos, int lineno, int colno, const std::string& tsval)
		: location_(new fLocation(pos, endPos, lineno, colno)), kind_(kind), strVal_(tsval) {
		if (kind_ == nullptr) {
			throw std::invalid_argument("Token kind cannot be null");
		}
	}

	const std::string& fToken::getTStrVal() const {
		return strVal_;
	}
	const fTKnd* fToken::getTKind() const {
		return kind_;
	}

	const fLocation* fToken::getLocation() const {
		return location_;
	}

	int fToken::radix() const {
		throw std::runtime_error("UnsupportedOperationException: radix() not supported for this token type");
	}

	std::string fToken::toString() const {
		std::ostringstream oss;
		oss << "fToken{kind=" << (kind_ ? kind_->toString() : "null")
			<< ", pos=" << location_->pos_
			<< ", endPos=" << location_->endPos_
			<< ", strVal='" << strVal_ << "'}";
		return oss.str();
	}
}