#include "ast/leaf/fThrow.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fThrow::fThrow(sp<fAstProdSubTreeN> &&throwExpr) : throwExpr_(std::move(throwExpr)) {
		if (this->throwExpr_ == nullptr) {
			throw std::invalid_argument("Throw expression cannot be null");
		}
	}

	void fThrow::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fThrow>(shared_from_this()), s);
	}

	std::string fThrow::toString() const {
		return "fThrow(throwExpr=" + (throwExpr_ ? throwExpr_->toString() : "null") + ")";
	}
}