#include "ast/leaf/fCaseClauses.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fCaseClauses::fCaseClauses(std::vector<std::shared_ptr<fCaseClause>> &&caseClauses) : _caseClauses(std::move(caseClauses)) {
		if (this->_caseClauses.empty()) {
			throw std::invalid_argument("Case clauses cannot be empty");
		}
	}

	const std::vector<std::shared_ptr<fCaseClause>> &fCaseClauses::getCaseClauses() {
		return _caseClauses;
	}

	void fCaseClauses::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fCaseClauses>(shared_from_this()), s);
	}

 std::string fCaseClauses::toString() const {
		std::string clausesStr;
		for (const auto& clause : _caseClauses) {
			if (!clausesStr.empty()) clausesStr += ", ";
			clausesStr += clause->toString();
		}
		return "CaseClauses(clauses=[" + clausesStr + "])";
 }
}