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

	class fTokenLocation {
		public:
		const int pos_, endPos_;
		const int lineno_, colno_;
		fTokenLocation(int pos, int endPos, int lineno, int colno) : pos_(pos), endPos_(endPos), lineno_(lineno), colno_(colno) {};
	};

	class fToken {
	protected:
		const fTokenLocation* location_;
		const fTKnd* kind_;
		std::string strVal_;

	public:
		static const fToken FILE_OFFSET;
		static const fToken ROOT_OPERATOR;

		static constexpr const char* OPERATOR = "_OPERATOR_";
		static constexpr const char* KEYWORD = "_KEYWORD_";
		static constexpr const char* INTERN = "_INTERN_";

		fToken(const fTKnd*  kind,  int pos, int endPos, int lineno, int colno, const std::string& tsval);
		virtual ~fToken() {
			if (location_ != nullptr) delete location_;
		}

		const std::string& getTStrVal() const ;
		const fTKnd* getTKind() const ;
		const fTokenLocation* getLocation() const ;

		virtual int radix() const ;

		std::string toString() const ;
	};


}