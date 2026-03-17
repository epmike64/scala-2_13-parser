#include "ast/leaf/fObject.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fTemplate.hpp"

namespace zebra::ast::leaf {

	fObject::fObject(const fToken* objectName, sp<fModifiers> &&modifiers, bool isCaseClass) : objectName_(objectName), modifiers_(std::move(modifiers)), isCaseClass_(isCaseClass) {
		if (this->objectName_ == nullptr) {
			throw std::invalid_argument("Object name token cannot be null");
		}
	}

	bool fObject::isCaseClass() const {
		return isCaseClass_;
	}

	sp<fModifiers> fObject::getModifiers() const {
		return modifiers_;
	}

	void fObject::setExtendsTemplate(sp<fTemplate> &&extendsTemplate) {
		this->extendsTemplate_ = std::move(extendsTemplate);
	}

	sp<fTemplate> fObject::getExtendsTemplate() const {
		return extendsTemplate_;
	}

	const fToken* fObject::getObjectName() const {
		return objectName_;
	}

	void fObject::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fObject>(shared_from_this()), s);
	}

	std::string fObject::toString() const {
		return "ObjectDef(name=" + objectName_->toString() +
		       ", isCaseClass=" + (isCaseClass_ ? "true" : "false") +
		       ", modifiers=" + (modifiers_ ? modifiers_->toString() : "null") +
		       ", extendsTemplate=" + (extendsTemplate_ ? extendsTemplate_->toString() : "null") + ")";
	}

}
