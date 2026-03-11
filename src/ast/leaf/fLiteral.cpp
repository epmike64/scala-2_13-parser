#include "ast/leaf/fLiteral.hpp"

namespace zebra::ast::leaf {

	std::string fLiteral::toString() const  {
		return "Literal(" + _literalName->toString() +")";
	}

}