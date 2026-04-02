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
		this->withType_ = std::move(withType);
	}

	sp<fClassConstr> fClassParents::getConstr() const {
		return constr_;
	}

	sp<fParamType> fClassParents::getWithType() const {
		return withType_;
	}

	void fClassParents::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fClassParents>(shared_from_this()), s);
	}

	std::string fClassParents::toString() const {
		return "ClassParents(constr=" + (constr_ ? constr_->toString() : "null") +
		       ", withTypes=" + (withType_ ? withType_->toString() : "null") + ")";
	}
}
