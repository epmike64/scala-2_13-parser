#include "ast/leaf/fLiteral.hpp"

#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {

	void fLiteral::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fLiteral>(shared_from_this()));
	}

	std::string fLiteral::toString() const  {
		return "Literal(" + _literalName->toString() +")";
	}

}
