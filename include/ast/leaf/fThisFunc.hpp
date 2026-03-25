#pragma once

#include "fFunc.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fThisFunc : public fFunc {
		sp<fParamClauses> clauses;
		sp<fConstrBlock> constrBlock;
	public:

		fThisFunc(sp<fModifiers> &&modifiers) ;

		 void setParamClauses(sp<fParamClauses> &&clauses) ;
		 void setConstrBlock(sp<fConstrBlock> &&constrBlock) ;
		 sp<fParamClauses> getParamClauses() const ;
		 sp<fConstrBlock> getConstrBlock() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return THIS_FUNC;
		 }
	};
}