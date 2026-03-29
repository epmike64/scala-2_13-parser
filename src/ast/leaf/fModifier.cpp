#include "ast/leaf/fModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fModifier::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fModifier>(shared_from_this()), s);
	}

	std::string fModifier::toString() const {
		return "Modifier(modifierType=" + fLangModifierTypeEToString(getModifierType()) + ")";
	}
}