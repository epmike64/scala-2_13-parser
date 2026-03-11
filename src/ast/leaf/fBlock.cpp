#include "ast/leaf/fBlock.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fBlock::addStmt(sp<fAstNod>&& stmt) {
		if (stmt == nullptr) {
			throw std::invalid_argument("Statement cannot be null");
		}
		_stmts.push_back(std::move(stmt));
	}

	std::vector<sp<fAstNod>>& fBlock::getStmts() { return _stmts; }

	void fBlock::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fBlock>(shared_from_this()));
	}

	std::string fBlock::toString() const {
		return "AccessModifier()";
	}
}