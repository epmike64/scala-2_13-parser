#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include <vector>

#include "../fLangOperand.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fBlock : public fLangOprnd {
		std::vector<sp<fAstNod>> _stmts;
		public:
		fBlock() = default;

		void addStmt(sp<fAstNod>&& stmt);

		std::vector<sp<fAstNod>>& getStmts();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::BLOCK;
		}
	};
}
