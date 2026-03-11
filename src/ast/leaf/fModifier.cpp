#include "ast/leaf/fModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fModifier::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fModifier>(shared_from_this()));
	}

	std::string fModifier::toString() const {
		return "AccessModifier()";
	}
}