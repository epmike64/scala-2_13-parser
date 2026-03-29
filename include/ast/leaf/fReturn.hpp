#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fReturn : public fLangOprnd {
		sp<fAstProdSubTreeN> returnExpr_;
		public:

		fReturn() = default;

		void setReturnExpr(sp<fAstProdSubTreeN> &&returnExpr);

		sp<fAstProdSubTreeN> getReturnExpr() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::RETURN;
		 }
	};
}