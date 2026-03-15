#pragma once

#include "fTypeParam.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fVariantTypeParam : public fTypeParam {
		lex::kind::fVarianceE variance_ = lex::kind::fVarianceE::INVARIANT;

	public:
		explicit fVariantTypeParam(lex::kind::fVarianceE variance) : variance_(variance) {
		}


		lex::kind::fVarianceE getVariance() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;
	};
}
