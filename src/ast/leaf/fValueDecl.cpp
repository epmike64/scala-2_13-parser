#include "ast/leaf/fValueDecl.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fValueDecl::fValueDecl(sp<fModifiers> &&modifiers) : fValue(std::move(modifiers)) {}

	void fValueDecl::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fValueDecl>(shared_from_this()));
	}

	std::string fValueDecl::toString() const {
		std::ostringstream oss;
		oss << "fValueDecl(" + fValueDecl::toString() + ")";
		return oss.str();
	}
}