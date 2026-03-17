#pragma once

namespace zebra::lex::kind {

	enum class fLangModifierTypeE {
		PRIVATE,
		PROTECTED,
		OVERRIDE,
		ABSTRACT,
		FINAL,
		OPEN,
		SEALED,
		IMPLICIT,
		LAZY
  };

	inline std::string fLangModifierTypeEToString(fLangModifierTypeE modType) {
		switch (modType) {
			case fLangModifierTypeE::PRIVATE: return "private";
			case fLangModifierTypeE::PROTECTED: return "protected";
			case fLangModifierTypeE::OVERRIDE: return "override";
			case fLangModifierTypeE::ABSTRACT: return "abstract";
			case fLangModifierTypeE::FINAL: return "final";
			case fLangModifierTypeE::OPEN: return "open";
			case fLangModifierTypeE::SEALED: return "sealed";
			case fLangModifierTypeE::IMPLICIT: return "implicit";
			case fLangModifierTypeE::LAZY: return "lazy";
			default:
				return "unknown modifier type";
		}
	}

} // namespace flint::compiler::frontend::lex::token
