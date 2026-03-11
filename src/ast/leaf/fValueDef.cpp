#include "ast/leaf/fValueDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {

	fValueDef::fValueDef(sp<fModifiers> &&modifiers) : fValue(std::move(modifiers)) {}


	void fValueDef::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fValueDef>(shared_from_this()));
	}

	std::string fValueDef::toString() const {
		return "fValueDef()";
	}

}
