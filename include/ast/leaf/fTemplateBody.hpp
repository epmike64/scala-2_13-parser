#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTemplateBody : public fAstOprndNod {
		std::vector<sp<fAstNod>> _stmts;
		public:

		fTemplateBody() = default;

		 void addStmt(sp<fAstNod>&& stmt) ;

		 std::vector<sp<fAstNod>>& getStmts() ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}