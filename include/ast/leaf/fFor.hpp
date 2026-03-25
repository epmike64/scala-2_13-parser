#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFor : public fLangOprnd {
		const std::vector<sp<fGenerator> > generators_;
		bool isYield_ = false;
		sp<fAstProdSubTreeN> yieldExpr_;

	public:
		fFor(std::vector<sp<fGenerator> > generators);

		const std::vector<sp<fGenerator> > &getGenerators() const;

		void setYield(bool isYield);

		bool isYield() const;

		void setYieldExpr(sp<fAstProdSubTreeN> &&yieldExpr);

		sp<fAstProdSubTreeN> getYieldExpr() const;


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::FOR;
		}
	};
}
