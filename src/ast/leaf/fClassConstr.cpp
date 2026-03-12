#include "ast/leaf/fClassConstr.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fClassConstr::fClassConstr(sp<fParamType> &&primaryCtorParamType) : paramType(std::move(primaryCtorParamType)) {
		if (this->paramType == nullptr) {
			throw std::invalid_argument("Primary constructor parameter type cannot be null");
		}
	}

	sp<fParamType> fClassConstr::getPrimaryCtorParamType() const {
		return paramType;
	}

	void fClassConstr::setArgsExpr(sp<fAstProdSubTreeN> &&args) {
		this->args_ = std::move(args);
	}

	sp<fAstProdSubTreeN> fClassConstr::getArgs() const {
		return args_;
	}

	void fClassConstr::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fClassConstr>(shared_from_this()));
	}

	std::string fClassConstr::toString() const {
		return "fClassConstr()";
	}
}