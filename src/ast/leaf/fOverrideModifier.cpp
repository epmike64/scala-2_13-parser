#include "ast/leaf/fOverrideModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fOverrideModifier::fOverrideModifier() : fModifier(lex::kind::fLangModifierTypeE::OVERRIDE) {}

	void fOverrideModifier::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fOverrideModifier>(shared_from_this()), s);
	}

	std::string fOverrideModifier::toString() const {
		return "AccessModifier()";
	}
}