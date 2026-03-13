#pragma once

#include <vector>

#include "fCaseClause.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fCaseClauses : public fAstOprndNod {
		const std::vector<std::shared_ptr<fCaseClause>> _caseClauses;
		public:

		fCaseClauses(std::vector<std::shared_ptr<fCaseClause>> &&caseClauses) ;

		const std::vector<std::shared_ptr<fCaseClause>> &getCaseClauses();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}