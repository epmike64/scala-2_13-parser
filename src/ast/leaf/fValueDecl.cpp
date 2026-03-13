#include "ast/leaf/fValueDecl.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fValueDecl::fValueDecl(sp<fModifiers> &&modifiers) : fValue(std::move(modifiers)) {}

	void fValueDecl::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fValueDecl>(shared_from_this()), s);
	}

	std::string fValueDecl::toString() const {
		std::ostringstream oss;
		oss << "fValueDecl(" + fValueDecl::toString() + ")";
		return oss.str();
	}
}