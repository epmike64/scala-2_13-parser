#include "ast/leaf/fIds.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fIds::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fIds>(shared_from_this()));
	}

	std::string fIds::toString() const {
		return "AccessModifier()";
	}
}