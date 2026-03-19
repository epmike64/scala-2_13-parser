#include "ast/leaf/fClassParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamType.hpp"

namespace zebra::ast::leaf {

	const fToken* fClassParam::getIdentifier() const {
		return identifier_;
	}

	const std::string fClassParam::getIdentName() const {
		if (identifier_ == nullptr) {
			throw std::runtime_error("Identifier token is null");
		}
		return identifier_->toString();
	}

	lex::kind::fVariableMutabilityTypeE fClassParam::getMutability() const {
		return mutability_;
	}
	sp<fParamType> fClassParam::getParamType() const {
		return paramType_;
	}
	sp<fAstProdSubTreeN> fClassParam::getDefaultValueExpr() const {
		return defaultValueExpr_;
	}
	sp<fModifiers> fClassParam::getModifiers() const {
		return modifiers_;
	}

	void fClassParam::setIdentifier(const fToken* identifier) {
		if (identifier == nullptr) {
			throw std::invalid_argument("Identifier token cannot be null");
		}
		this->identifier_ = identifier;
	}

	void fClassParam::setMutability(lex::kind::fVariableMutabilityTypeE mutability) {
		this->mutability_ = mutability;
	}


	void fClassParam::setParamType(sp<fParamType> &&paramType) {
		if (paramType == nullptr) {
			throw std::invalid_argument("Parameter type cannot be null");
		}
		this->paramType_ = std::move(paramType);
	}

	void fClassParam::setDefaultValueExpr(sp<fAstProdSubTreeN> &&defaultValue) {
		this->defaultValueExpr_ = std::move(defaultValue);
	}

	void fClassParam::setModifiers(sp<fModifiers> &&modifiers) {
		this->modifiers_ = std::move(modifiers);
	}


	void fClassParam::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fClassParam>(shared_from_this()), s);
	}

	std::string fClassParam::toString() const {
		return "fClassParam(identifier=" + (identifier_ ? identifier_->toString() : "null") +
		       ", mutability=" + (mutability_ == lex::kind::fVariableMutabilityTypeE::VAL ? "val" :
		                          mutability_ == lex::kind::fVariableMutabilityTypeE::VAR ? "var" : "none") +
		       ", paramType=" + (paramType_ ? paramType_->toString() : "null") +
		       ", defaultValueExpr=" + (defaultValueExpr_ ? defaultValueExpr_->toString() : "null") +
		       ", modifiers=" + (modifiers_ ? modifiers_->toString() : "null") + ")";
	}
}
