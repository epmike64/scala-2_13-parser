#include "ast/leaf/fClassDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fTemplate.hpp"

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
		if (classParamClauses != nullptr) {
			this->classParamClauses_ = std::move(classParamClauses);
		}
	}


	void fClassDef::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fClassDef>(shared_from_this()), s);
	}

	std::string fClassDef::toString() const {
		std::stringstream out;
		out << "ClassDef(name=" + getIdentToken()->toString() + ", isCaseClass=" + (isCaseClass_ ? "true" : "false");
		out << (constrAccessModifier_ ? ", constrAccessModifier=" + constrAccessModifier_->toString() : "");

		std::string typeParamsStr;
		if (typeParamClause_) {
			typeParamsStr = typeParamClause_->toString();
		}

		out << (classParamClauses_ ? ", classParamClauses=" + classParamClauses_->toString() : "");
		out << (" , modifiers=" + (getModifiers() ? getModifiers()->toString() : "null"));


		out << (" , typeParams=[" + typeParamsStr + "]");
		out << (" , extendsTemplate=" + (getExtendsTemplate() ? getExtendsTemplate()->toString() : "null") + ")\n");
		return out.str();
	}
}
