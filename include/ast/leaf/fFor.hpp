#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFor : public fAstOprndNod {
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


		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;

		std::string toString() const override;
	};
}
