#include "ast/leaf/fFun.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fFun::fFun(sp<fModifiers> &&modifiers) : modifiers_(std::move(modifiers)) {
	}

	sp<fModifiers> fFun::getModifiers() const {
		return modifiers_;
	}


	void fFun::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fFun>(shared_from_this()), s);
	}

	std::string fFun::toString() const {
		return "fFun()";
	}
}