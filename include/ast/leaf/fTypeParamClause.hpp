#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fTypeParamClause : public fAstOprndNod {
		sp<std::vector<sp<fVariantTypeParam>>> variantTypeParams_;
	public:
		fTypeParamClause(sp<std::vector<sp<fVariantTypeParam>>> variantTypeParams);
		sp<std::vector<sp<fVariantTypeParam>>> getVariantTypeParams() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}