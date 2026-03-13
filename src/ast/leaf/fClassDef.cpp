#include "ast/leaf/fClassDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fClassDef::fClassDef(const fToken *className, sp<fModifiers> &&modifiers, bool isCaseClass) : fTraitDef(className,
			std::move(modifiers)), isCaseClass_(isCaseClass) {
	}

	void fClassDef::setConstrAccessModifier(sp<fAccessModifier> &&constrAccessModifier) {
		this->constrAccessModifier_ = std::move(constrAccessModifier);
	}

	sp<fAccessModifier> fClassDef::getConstrAccessModifier() {
		return constrAccessModifier_;
	}

	void fClassDef::setClassParamClauses(sp<fClassParamClauses> &&classParamClauses) {
		this->classParamClauses_ = std::move(classParamClauses);
	}


	void fClassDef::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fClassDef>(shared_from_this()), s);
	}

	std::string fClassDef::toString() const {
		return "ClassDef(name=" + getName()->toString() + ", isCaseClass=" + (isCaseClass_ ? "true" : "false") + ")";
	}
}
