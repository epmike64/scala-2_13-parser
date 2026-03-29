#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTemplateBody : public fLangOprnd {
		std::vector<sp<fAstNod>> _stmts;
		public:

		fTemplateBody() = default;

		 void addStmt(sp<fAstNod>&& stmt) ;

		 std::vector<sp<fAstNod>>& getStmts() ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TEMPLATE_BODY;
		 }
	};
}