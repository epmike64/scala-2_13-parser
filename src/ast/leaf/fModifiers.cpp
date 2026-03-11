#include "ast/leaf/fModifiers.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	void fModifiers::setAccessModifier(sp<fAccessModifier> &&accessModifier) {
		this->accessModifier_ = std::move(accessModifier);
	}

	void fModifiers::setOverrideModifier(sp<fOverrideModifier> &&overrideModifier) {
		this->overrideModifier_ = std::move(overrideModifier);
	}

	void fModifiers::setLocalModifier(sp<fLocalModifier> &&localModifier) {
		this->localModifier_ = std::move(localModifier);
	}

	sp<fAccessModifier> fModifiers::getAccessModifier() const {
		return accessModifier_;
	}

	sp<fOverrideModifier> fModifiers::getOverrideModifier() const {
		return overrideModifier_;
	}

	sp<fLocalModifier> fModifiers::getLocalModifier() const {
		return localModifier_;
	}

	void fModifiers::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fModifiers>(shared_from_this()));
	}

	std::string fModifiers::toString() const {
		return "AccessModifier()";
	}
}