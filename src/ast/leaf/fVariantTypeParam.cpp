#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fVariantTypeParam::fVariantTypeParam(const fToken* identifier) : fTypeParam(identifier) {}

	void fVariantTypeParam::setVariance(lex::kind::fVarianceE variance) {
		this->variance_ = variance;
	}

	lex::kind::fVarianceE fVariantTypeParam::getVariance() const {
		return variance_;
	}

	void fVariantTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fVariantTypeParam>(shared_from_this()));
	}

	std::string fVariantTypeParam::toString() const {
		return "AccessModifier()";
	}
}