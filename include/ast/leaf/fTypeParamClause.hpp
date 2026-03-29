#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
// fAstNodVisitor is forward-declared by fAstOprndNod.hpp
#include "util/fCommon.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fTypeParamClause : public fLangOprnd {
		sp<std::vector<sp<fVariantTypeParam>>> variantTypeParams_;
	public:
		fTypeParamClause(sp<std::vector<sp<fVariantTypeParam>>> variantTypeParams);
		sp<std::vector<sp<fVariantTypeParam>>> getVariantTypeParams() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TYPE_PARAM_CLAUSE;
		 }
	};
}