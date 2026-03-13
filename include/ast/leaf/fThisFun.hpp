#pragma once

#include "fFun.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fThisFun : public fFun {
		sp<fParamClauses> clauses;
		sp<fConstrBlock> constrBlock;
	public:

		fThisFun(sp<fModifiers> &&modifiers) ;

		 void setParamClauses(sp<fParamClauses> &&clauses) ;
		 void setConstrBlock(sp<fConstrBlock> &&constrBlock) ;
		 sp<fParamClauses> getParamClauses() const ;
		 sp<fConstrBlock> getConstrBlock() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}