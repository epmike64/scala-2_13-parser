#include "ast/leaf/fClassParents.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fClassParents::setConstr(sp<fClassConstr> &&constr) {
		if (constr == nullptr) {
			throw std::invalid_argument("Constructor cannot be null");
		}
		this->constr_ = std::move(constr);
	}

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

	void fClassParents::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fClassParents>(shared_from_this()));
	}

	std::string fClassParents::toString() const {
		return "AccessModifier()";
	}
}