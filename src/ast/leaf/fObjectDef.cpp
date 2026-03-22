#include "ast/leaf/fObjectDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fTemplate.hpp"

namespace zebra::ast::leaf {

	fObjectDef::fObjectDef(const fToken* objectName, sp<fModifiers> &&modifiers, bool isCaseClass) : identName_(objectName), modifiers_(std::move(modifiers)), isCaseClass_(isCaseClass) {
		if (this->identName_ == nullptr) {
			throw std::invalid_argument("Object name token cannot be null");
		}
	}

	bool fObjectDef::isCaseClass() const {
		return isCaseClass_;
	}

	sp<fModifiers> fObjectDef::getModifiers() const {
		return modifiers_;
	}

	void fObjectDef::setExtendsTemplate(sp<fTemplate> &&extendsTemplate) {
		this->extendsTemplate_ = std::move(extendsTemplate);
	}

	sp<fTemplate> fObjectDef::getExtendsTemplate() const {
		return extendsTemplate_;
	}

	const fToken* fObjectDef::getIdentToken() const {
		return identName_;
	}

	const std::string& fObjectDef::getIdentName() const {
		return identName_->getTStrVal();
	}

	void fObjectDef::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fObjectDef>(shared_from_this()), s);
	}

	std::string fObjectDef::toString() const {
		return "ObjectDef(name=" + identName_->toString() +
		       ", isCaseClass=" + (isCaseClass_ ? "true" : "false") +
		       ", modifiers=" + (modifiers_ ? modifiers_->toString() : "null") +
		       ", extendsTemplate=" + (extendsTemplate_ ? extendsTemplate_->toString() : "null") + ")";
	}

}
