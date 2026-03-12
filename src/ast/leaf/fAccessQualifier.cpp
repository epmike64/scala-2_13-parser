#include "ast/leaf/fAccessQualifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fAccessQualifier::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast< fAccessQualifier>(shared_from_this()));
	}

	std::string  fAccessQualifier::toString() const {
		return "AccessQualifier()";
	}
}