#pragma once

#include "fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fThrow : public fLangOprnd {
		const sp<fAstProdSubTreeN> throwExpr_;
		public:

		fThrow(sp<fAstProdSubTreeN> &&throwExpr);

		 sp<fAstProdSubTreeN> getThrowExpr() const {
			return throwExpr_;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor,esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return THROW;
		 }
	};
}