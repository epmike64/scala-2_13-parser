#include "../../../include/lex/util/fLangMethNameCheck.hpp"
#include <cctype>

namespace zebra::lex::kind {

// Static member initialization
const std::unordered_set<std::string> fLangMethNameCheck::SCALA_KEYWORDS = {
    "abstract", "case", "catch", "class", "def", "do", "else", "extends", "false",
    "final", "finally", "for", "forSome", "if", "implicit", "import", "lazy",
    "match", "new", "null", "object", "override", "package", "private", "protected",
    "return", "sealed", "super", "this", "throw", "trait", "true", "try", "type",
    "val", "var", "while", "with", "yield"
};

const std::regex fLangMethNameCheck::VALID_ALPHA_METHOD(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
const std::regex fLangMethNameCheck::VALID_SYMBOLIC_METHOD(R"(^[!#%&*+/:<=>?@\^|~-]+$)");
const std::regex fLangMethNameCheck::VALID_BACKTICK_METHOD(R"(^`[^`]+`$)");

bool fLangMethNameCheck::isMNameValid(const std::string& methodName) {
    // Empty or null names are invalid
    if (methodName.empty()) {
        return false;
    }
    
    // Check if the method name is a reserved keyword (unless enclosed in backticks)
    if (SCALA_KEYWORDS.find(methodName) != SCALA_KEYWORDS.end()) {
        return false;
    }
    
    // Check if the method name is an alphanumeric name
    if (std::regex_match(methodName, VALID_ALPHA_METHOD)) {
        return true;
    }
    
    // Check if the method name is a valid symbolic operator
    if (std::regex_match(methodName, VALID_SYMBOLIC_METHOD)) {
        return true;
    }
    
    // Check if the method name is enclosed in backticks (valid for any name)
    if (std::regex_match(methodName, VALID_BACKTICK_METHOD)) {
        return true;
    }
    
    // Check if the name starts with a number (invalid)
    if (std::isdigit(static_cast<unsigned char>(methodName[0]))) {
        return false;
    }
    
    // Invalid if it contains spaces and is not enclosed in backticks
    if (methodName.find(' ') != std::string::npos && methodName[0] != '`') {
        return false;
    }
    
    // Invalid if it contains a dot (.)
    if (methodName.find('.') != std::string::npos) {
        return false;
    }
    
    // If none of the valid cases matched, it's invalid
    return false;
}

} // namespace flint::compiler::frontend::lang