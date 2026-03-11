#pragma once

namespace zebra::lex::kind {
	enum class fTTagE {
		NAME_VAL,  STRING, NUMERIC, KEYWORD, OPERATOR, INTERN
	};

	constexpr const char* fTTagE_Tostring(fTTagE tag) {
		switch (tag) {
			case fTTagE::NAME_VAL:   return "NAME_VAL";
			case fTTagE::STRING: return "STRING";
			case fTTagE::NUMERIC:  return "NUMERIC";
			case fTTagE::KEYWORD:  return "KEYWORD";
			case fTTagE::OPERATOR:  return "OPERATOR";
			case fTTagE::INTERN:  return "INTERN";
		}
	}
}
