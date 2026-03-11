
#pragma once

#include <string>
#include <cassert>

#include "fToken.hpp"

namespace zebra::lex::token {

	using kind::fTKnd;
	using kind::fTTagE;

	class fNumToken : public fToken {
		int _radix;

	public:

		fNumToken(const fTKnd* kind, int pos, int endPos, std::string& tsval, int radix)
			 : fToken(kind, pos, endPos, tsval), _radix(radix) {
		}

		int getRadix() const  {
			return _radix;
		}
	};

}