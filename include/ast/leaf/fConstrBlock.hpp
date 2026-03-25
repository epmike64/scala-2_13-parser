#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fConstrBlock : public fLangOprnd {
		sp<fAstProdSubTreeN> argExprs_;
		std::vector<sp<fAstNod>> blockStmts_;
		public:

		fConstrBlock() = default;

		 void setArgExprs(sp<fAstProdSubTreeN> &&argExprs);

		 void addBlockStmt(sp<fAstOprndNod> && stmt) ;

		 sp<fAstProdSubTreeN> getArgExprs() const;


		 std::vector<sp<fAstNod>>& getBlockStmts();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return CONSTR_BLOCK;
		}
	};
}