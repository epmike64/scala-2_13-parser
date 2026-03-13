#pragma once

#include "fTypeParam.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fVariantTypeParam : public fTypeParam {
		lex::kind::fVarianceE variance_ = lex::kind::fVarianceE::NONE;
		public:

		fVariantTypeParam(const fToken* identifier) ;

		 void setVariance(lex::kind::fVarianceE variance) ;

		 lex::kind::fVarianceE getVariance() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}