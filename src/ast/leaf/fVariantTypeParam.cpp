#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fVariantTypeParam::setVariance(lex::kind::fVarianceE variance) {
		this->variance_ = variance;
	}

	lex::kind::fVarianceE fVariantTypeParam::getVariance() const {
		return variance_;
	}

	void fVariantTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fVariantTypeParam>(shared_from_this()), s);
	}

	std::string fVariantTypeParam::toString() const {
		return "VariantTypeParam(variance=" + std::to_string(static_cast<int>(variance_)) + ")";
	}
}