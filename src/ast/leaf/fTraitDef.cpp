#include "ast/leaf/fTraitDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTraitDef::fTraitDef(const fToken* traitName, sp<fModifiers> &&modifiers) : traitName_(traitName), modifiers_(std::move(modifiers)) {
		if (this->traitName_ == nullptr) {
			throw std::invalid_argument("Trait name token cannot be null");
		}
	}

	const fToken* fTraitDef::getName() const {
		return traitName_;
	}

	sp<fModifiers> fTraitDef::getModifiers() const {
		return modifiers_;
	}

	void fTraitDef::setTypeParams(std::vector<sp<fVariantTypeParam>> &&typeParams) {
		this->typeParams_ = std::move(typeParams);
	}

	std::vector<sp<fVariantTypeParam>> fTraitDef::getTypeParams() const {
		return typeParams_;
	}

	void fTraitDef::setExtendsTemplate(sp<fTemplate> &&extendsTemplate) {
		this->extendsTemplate_ = std::move(extendsTemplate);
	}

	sp<fTemplate> fTraitDef::getExtendsTemplate() const {
		return extendsTemplate_;
	}


	void fTraitDef::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fTraitDef>(shared_from_this()), s);
	}

	std::string fTraitDef::toString() const {
		return "AccessModifier()";
	}
}