#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fConstrBlock : public fLangOprnd {
		PVecP<fAstProdSubTreeN> argExprs_;
		PVecP<fAstNod> blockStmts_;
		public:

		 fConstrBlock() = default;

		bool isSelfInvocation()  {
			return argExprs_ != nullptr;
		}

		 void addArgExprs(sp<fAstProdSubTreeN>&& argExpr);

		 void addBlockStmt(sp<fAstNod> && stmt) ;

		 PVecP<fAstProdSubTreeN> getArgExprs();

		PVecP<fAstNod> getBlockStmts();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::CONSTR_BLOCK;
		}
	};
}