#include "ast/leaf/fLocalModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fLocalModifier::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fLocalModifier>(shared_from_this()), s);
	}

	std::string fLocalModifier::toString() const {
		return "LocalModifier(modifierType=" + fLangModifierTypeEToString(getModifierType()) + ")";
	}
}