#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include <vector>

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fBlock : public fAstOprndNod {
		std::vector<sp<fAstNod>> _stmts;
		public:
		fBlock() = default;

		void addStmt(sp<fAstNod>&& stmt);

		std::vector<sp<fAstNod>>& getStmts();

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}