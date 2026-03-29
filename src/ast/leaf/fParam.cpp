
#include "ast/leaf/fParam.hpp"

#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fParamType.hpp"

namespace zebra::ast::leaf {

	fParam::fParam(const fToken* identifier) : identifier_(identifier) {
		if (this->identifier_ == nullptr) {
			throw std::invalid_argument("Parameter identifier cannot be null");
		}
	}

	void fParam::setParamType(sp<fParamType> &&paramType) {
		this->paramType_ = std::move(paramType);
	}

	void fParam::setDefaultValueExpr(sp<fAstProdSubTreeN> &&defaultValue) {
		this->defaultValue_ = std::move(defaultValue);
	}

	const fToken* fParam::getIdentToken() const {
		return identifier_;
	}

	const std::string fParam::getIdentName() const {
		return identifier_->getTStrVal();
	}

	sp<fParamType> fParam::getParamType() const {
		return paramType_;
	}

	sp<fAstProdSubTreeN> fParam::getDefaultValueExpr() const {
		return defaultValue_;
	}

	void fParam::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fParam>(shared_from_this()), s);
	}

	std::string fParam::toString() const {
		return "fParam(identifier=" + (identifier_ ? identifier_->toString() : "null") +
		       ", paramType=" + (paramType_ ? paramType_->toString() : "null") +
		       ", defaultValue=" + (defaultValue_ ? defaultValue_->toString() : "null") + ")";
	}
}
