#include "ast/leaf/fLocalModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fLocalModifier::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fLocalModifier>(shared_from_this()));
	}

	std::string fLocalModifier::toString() const {
		return "AccessModifier()";
	}
}