#pragma once
#include <string>
#include <stdexcept>
#include <cassert>
#include <memory>

#include "lex/kind/fTTagE.hpp"
#include "lex/kind/fTKnd.hpp"
#include <sstream>

namespace zebra::lex::token {

	using namespace zebra::lex::kind;

	class fToken {
	protected:
		int pos_, endPos_;
		const fTKnd* kind_;
		std::string strVal_;

	public:
		static const fToken FILE_OFFSET;
		static const fToken ROOT_OPERATOR;

		static constexpr const char* OPERATOR = "_OPERATOR_";
		static constexpr const char* KEYWORD = "_KEYWORD_";
		static constexpr const char* INTERN = "_INTERN_";

		fToken(const fTKnd*  kind,  int pos, int endPos, const std::string& tsval):
			pos_(pos), endPos_(endPos), kind_(kind), strVal_(tsval) {
		}


		const std::string& getTStrVal() const {
			return strVal_;
		}
		const fTKnd* getTKind() const {
			return kind_;
		}

		virtual int radix() const {
			throw std::runtime_error("UnsupportedOperationException: radix() not supported for this token type");
		}

		std::string toString() const {
			std::ostringstream oss;
			oss << "fToken{kind=" << (kind_ ? kind_->toString() : "null")
				<< ", pos=" << pos_
				<< ", endPos=" << endPos_
				<< ", strVal='" << strVal_ << "'}";
			return oss.str();
		}
	};


}