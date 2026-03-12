#include "ast/leaf/fId.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fId::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fId>(shared_from_this()));
	}

	std::string fId::toString() const {
		return "id(" + _id->toString() + ")";
	}
}