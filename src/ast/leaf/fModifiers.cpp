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

	void fModifiers::addLocalModifier(sp<fLocalModifier> &&localModifier) {
		if (localModifiers_ == nullptr) {
			localModifiers_ = ms<std::vector<sp<fLocalModifier>>>();
		}
		localModifiers_->push_back(std::move(localModifier));
	}

	sp<fAccessModifier> fModifiers::getAccessModifier() const {
		return accessModifier_;
	}

	sp<fOverrideModifier> fModifiers::getOverrideModifier() const {
		return overrideModifier_;
	}

	sp<std::vector<sp<fLocalModifier>>> fModifiers::getLocalModifiers() const {
		return localModifiers_;
	}

	void fModifiers::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fModifiers>(shared_from_this()), s);
	}

	std::string fModifiers::toString() const {
		return "AccessModifier()";
	}
}