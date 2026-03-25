#pragma once

#include "fTypeParam.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fVariantTypeParam : public fLangOprnd {
		fVarianceE variance_ = fVarianceE::INVARIANT;
		sp<fTypeParam> typeParam_;
	public:
		explicit fVariantTypeParam(lex::kind::fVarianceE variance) : variance_(variance) {
		}

		 void setTypeParam(const sp<fTypeParam> &typeParam) ;

		sp<fTypeParam> getTypeParam();
		lex::kind::fVarianceE getVariance() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return VARIANT_TYPE_PARAM;
		 }
	};
}
