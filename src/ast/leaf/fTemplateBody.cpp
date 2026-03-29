#include "ast/leaf/fTemplateBody.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fTemplateBody::addStmt(sp<fAstNod>&& stmt) {
		if (stmt == nullptr) {
			throw std::invalid_argument("Statement cannot be null");
		}
		this->_stmts.push_back(std::move(stmt));
	}

	std::vector<sp<fAstNod>>& fTemplateBody::getStmts() {
		return _stmts;
	}


	void fTemplateBody::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fTemplateBody>(shared_from_this()), s);
	}

	std::string fTemplateBody::toString() const {
		return "TemplateBody(stmts=[" + [&]() {
			std::string result;
			for (const auto& stmt : _stmts) {
				result += (stmt ? stmt->toString() : "null") + ", ";
			}
			return result;
		}() + "])";
	}
}