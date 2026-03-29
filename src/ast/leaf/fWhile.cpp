#include "ast/leaf/fWhile.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {

	fWhile::fWhile(sp<fAstProdSubTreeN> &&condExpr) : condExpr(std::move(condExpr)) {
		if (this->condExpr == nullptr) {
			throw std::invalid_argument("Condition expression cannot be null");
		}
	}

	sp<fAstProdSubTreeN> fWhile::getCondExpr() const {
		return condExpr;
	}

	void fWhile::setWhileBody(sp<fAstProdSubTreeN> &&body) {
		this->body = std::move(body);
	}

	sp<fAstProdSubTreeN> fWhile::getBody() const {
		return body;
	}


	void fWhile::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fWhile>(shared_from_this()), s);
	}

	std::string fWhile::toString() const {
		return "while (" + condExpr->toString() + ") " + body->toString();
	}



}