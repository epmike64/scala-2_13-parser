#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fReturn : public fAstOprndNod {
		sp<fAstProdSubTreeN> returnExpr_;
		public:

		fReturn() = default;

		void setReturnExpr(sp<fAstProdSubTreeN> &&returnExpr);

		sp<fAstProdSubTreeN> getReturnExpr() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}