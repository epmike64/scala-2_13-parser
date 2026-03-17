#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	lex::kind::fVarianceE fVariantTypeParam::getVariance() const {
		return variance_;
	}

	void fVariantTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fVariantTypeParam>(shared_from_this()), s);
	}

	std::string fVariantTypeParam::toString() const {
		const std::string varianceStr = variance_ == lex::kind::fVarianceE::INVARIANT  ? "invariant" :
		                                variance_ == lex::kind::fVarianceE::COVARIANT   ? "covariant" : "contravariant";
		return "fVariantTypeParam(variance=" + varianceStr +
		       ", base=" + fTypeParam::toString() + ")";
	}
}