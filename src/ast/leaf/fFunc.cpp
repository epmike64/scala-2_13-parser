#include "ast/leaf/fFunc.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fModifiers.hpp"

namespace zebra::ast::leaf {

	fFunc::fFunc(sp<fModifiers> &&modifiers) : modifiers_(std::move(modifiers)) {
	}

	sp<fModifiers> fFunc::getModifiers() const {
		return modifiers_;
	}


	void fFunc::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fFunc>(shared_from_this()), s);
	}

	std::string fFunc::toString() const {
		return "Fun(modifiers=" + (modifiers_ ? modifiers_->toString() : "null") + ")";
	}
}
