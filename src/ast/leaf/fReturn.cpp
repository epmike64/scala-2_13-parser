#include "ast/leaf/fReturn.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {
	
	void fReturn::setReturnExpr(sp<fAstProdSubTreeN> &&returnExpr) {
		this->returnExpr_ = std::move(returnExpr);
	}

	sp<fAstProdSubTreeN> fReturn::getReturnExpr() const {
		return returnExpr_;
	}

	void fReturn::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fReturn>(shared_from_this()), s);
	}

	std::string fReturn::toString() const {
		return "fReturn(returnExpr=" + (returnExpr_ ? returnExpr_->toString() : "null") + ")";
	}
}