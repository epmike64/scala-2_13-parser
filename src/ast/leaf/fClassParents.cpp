#include "ast/leaf/fClassParents.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fClassConstr.hpp"

namespace zebra::ast::leaf {

	fClassParents::fClassParents(sp<fClassConstr> &&constr): constr_(constr){}

	void fClassParents::setWithType(sp<fParamType> &&withType) {
		if (withType == nullptr) {
			throw std::invalid_argument("With type cannot be null");
		}
		this->withTypes_ = std::move(withType);
	}

	sp<fClassConstr> fClassParents::getConstr() const {
		return constr_;
	}

	sp<fParamType> fClassParents::getWithTypes() const {
		return withTypes_;
	}

	void fClassParents::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fClassParents>(shared_from_this()), s);
	}

	std::string fClassParents::toString() const {
		return "ClassParents(constr=" + (constr_ ? constr_->toString() : "null") +
		       ", withTypes=" + (withTypes_ ? withTypes_->toString() : "null") + ")";
	}
}
