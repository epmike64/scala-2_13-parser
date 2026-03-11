#pragma once

#include <string>
#include <unordered_set>
#include <regex>

namespace zebra::lex::kind {

	class fLangMethNameCheck {
	public:
		// Check if a method name is valid
		static bool isMNameValid(const std::string& methodName);

	private:
		// Set of Scala reserved keywords
		static const std::unordered_set<std::string> SCALA_KEYWORDS;

		// Regex patterns for Scala method names
		static const std::regex VALID_ALPHA_METHOD;
		static const std::regex VALID_SYMBOLIC_METHOD;
		static const std::regex VALID_BACKTICK_METHOD;

		// Private constructor - this is a utility class
		fLangMethNameCheck() = delete;
		fLangMethNameCheck(const fLangMethNameCheck&) = delete;
		fLangMethNameCheck& operator=(const fLangMethNameCheck&) = delete;
	};

} // namespace flint::compiler::frontend::lang