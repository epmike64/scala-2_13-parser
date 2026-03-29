#include "ast/leaf/fTraitDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fTemplate.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"

namespace zebra::ast::leaf {

	fTraitDef::fTraitDef(const fToken* traitName, sp<fModifiers> &&modifiers) : identName_(traitName), modifiers_(std::move(modifiers)) {
		if (this->identName_ == nullptr) {
			throw std::invalid_argument("Trait name token cannot be null");
		}
	}

	const fToken* fTraitDef::getIdentToken() const {
		return identName_;
	}

	const std::string& fTraitDef::getIdentName() const {
		return identName_->getTStrVal();
	}

	sp<fModifiers> fTraitDef::getModifiers() const {
		return modifiers_;
	}

	void fTraitDef::setTypeParamClause(const sp<fTypeParamClause>& typeParams) {
		this->typeParamClause_ =typeParams;
	}

	sp<fTypeParamClause> fTraitDef::getTypeParamClause() const {
		return typeParamClause_;
	}

	void fTraitDef::setExtendsTemplate(sp<fTemplate> &&extendsTemplate) {
		this->extendsTemplate_ = std::move(extendsTemplate);
	}

	sp<fTemplate> fTraitDef::getExtendsTemplate() const {
		return extendsTemplate_;
	}


	void fTraitDef::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fTraitDef>(shared_from_this()), s);
	}

	std::string fTraitDef::toString() const {
		std::string typeParamsStr;
		if (typeParamClause_) {
			// for (const auto &tp: *typeParams_) {
			// 	if (!typeParamsStr.empty()) typeParamsStr += ", ";
			// 	typeParamsStr += tp->toString();
			// }
			typeParamsStr = typeParamClause_->toString();
		}
		return "TraitDef(name=" + getIdentToken()->toString() +
		       ", modifiers=" + (modifiers_ ? modifiers_->toString() : "null") +
		       ", typeParams=[" + typeParamsStr + "]" +
		       ", extendsTemplate=" + (extendsTemplate_ ? extendsTemplate_->toString() : "null") + ")";
	}
}
