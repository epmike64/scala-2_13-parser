#include "ast/leaf/fClassConstr.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fClassConstr::fClassConstr(sp<fParamType> &&paramType) : paramType_(std::move(paramType)) {
		if (this->paramType_ == nullptr) {
			throw std::invalid_argument("Primary constructor parameter type cannot be null");
		}
	}

	sp<fParamType> fClassConstr::getParamType() const {
		return paramType_;
	}

	void fClassConstr::setArgsExpr(sp<fAstProdSubTreeN> &&args) {
		this->args_ = std::move(args);
	}

	sp<fAstProdSubTreeN> fClassConstr::getArgs() const {
		return args_;
	}

	void fClassConstr::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fClassConstr>(shared_from_this()), s);
	}

	std::string fClassConstr::toString() const {
		return "fClassConstr(paramType=" + (paramType_ ? paramType_->toString() : "null") +
		       ", args=" + (args_ ? args_->toString() : "null") + ")";
	}
}