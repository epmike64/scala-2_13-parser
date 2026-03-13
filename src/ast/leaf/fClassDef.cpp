#include "ast/leaf/fClassDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fClassDef::fClassDef(const fToken *className, sp<fModifiers> &&modifiers, bool isCaseClass) : fTraitDef(className,
			std::move(modifiers)), isCaseClass_(isCaseClass) {
	}

	void fClassDef::setConstructorAccessModifier(sp<fAccessModifier> &&constructorAccessModifier) {
		this->constructorAccessModifier_ = std::move(constructorAccessModifier);
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
