#include "ast/leaf/fAccessModifier.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fAccessQualifier.hpp"

namespace zebra::ast::leaf {

	void fAccessModifier::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fAccessModifier>(shared_from_this()), s);
	}

	void fAccessModifier::setQualifier(sp<fAccessQualifier> &&qualifier) {
		if (qualifier == nullptr) {
			throw std::invalid_argument("Access qualifier cannot be null");
		}
		this->qualifier_ = std::move(qualifier);
	}

	std::string fAccessModifier::toString() const {
		return "AccessModifier(modifierType=" + fLangModifierTypeEToString(getModifierType()) +
		       ", qualifier=" + (qualifier_ ? qualifier_->toString() : "null") + ")";
	}
}
