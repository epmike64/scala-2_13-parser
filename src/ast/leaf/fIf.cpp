
#include <string>
#include "ast/leaf/fIf.hpp"

namespace zebra::ast::leaf {

	void fIf::setIfBody(sp<fAstProdSubTreeN> &&ifBody) {
		if (ifBody == nullptr) {
			throw std::invalid_argument("If body cannot be null");
		}
		this->ifBody = std::move(ifBody);
	}

	void fIf::setElseBody(sp<fAstProdSubTreeN> &&elseBody) {
		this->elseBody = std::move(elseBody);
	}


	void fIf::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fIf>(shared_from_this()), s);
	}

	std::string fIf::toString() const {
		std::string result = "If(cond: " + condExpr->toString() + ", ifBody: " + (ifBody ? ifBody->toString() : "null");
		if (elseBody) {
			result += ", elseBody: " + elseBody->toString();
		}
		result += ")";
		return result;
	}

}