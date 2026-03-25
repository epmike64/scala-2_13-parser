#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTry : public fLangOprnd {
		const sp<fAstProdSubTreeN> tryBlock_;
		sp<fAstProdSubTreeN> catchBlock_;
		sp<fAstProdSubTreeN> finallyBlock_;

		public:

		fTry(sp<fAstProdSubTreeN> &&tryBlock);

		 void setCatchBlock(sp<fAstProdSubTreeN> &&catchBlock);
		 void setFinallyBlock(sp<fAstProdSubTreeN> &&finallyBlock);

		 sp<fAstProdSubTreeN> getTryBlock() const;

		 sp<fAstProdSubTreeN> getCatchBlock() const ;

		 sp<fAstProdSubTreeN> getFinallyBlock() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TRY;
		 }
	};
}