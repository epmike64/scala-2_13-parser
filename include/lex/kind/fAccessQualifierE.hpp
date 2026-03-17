#pragma once

namespace zebra::lex::kind {

	enum class fAccessQualifierE {
		ID, THIS
  };

	inline std::string fAccessQualifierEToString(fAccessQualifierE qualifier) {
		switch (qualifier) {
			case fAccessQualifierE::ID:
				return "ID";
			case fAccessQualifierE::THIS:
				return "THIS";
			default:
				return "Unknown AccessQualifierE";
		}
	}

} 