#include "ast/leaf/fClassParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	const fToken* fClassParam::getIdentifier() const {
		return identifier_;
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


	void fClassParam::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fClassParam>(shared_from_this()));
	}

	std::string fClassParam::toString() const {
		return "AccessModifier()";
	}
}