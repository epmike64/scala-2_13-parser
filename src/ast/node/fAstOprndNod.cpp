#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::node {

	void fAstOprndNod::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fAstOprndNod>(shared_from_this()));
	}

	std::string fAstOprndNod::toString() const {
		return "AstOprndNod";
	}
} // namespace zebra::ast::node

