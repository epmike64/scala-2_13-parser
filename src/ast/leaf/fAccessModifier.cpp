#include "ast/leaf/fAccessModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fAccessModifier::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fAccessModifier>(shared_from_this()));
	}

	void fAccessModifier::setQualifier(sp<fAccessQualifier> &&qualifier) {
		if (qualifier == nullptr) {
			throw std::invalid_argument("Access qualifier cannot be null");
		}
		this->qualifier_ = std::move(qualifier);
	}

	std::string fAccessModifier::toString() const {
		return "AccessModifier()";
	}
}