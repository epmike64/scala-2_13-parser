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

	void fVariantTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fVariantTypeParam>(shared_from_this()), s);
	}

	std::string fVariantTypeParam::toString() const {
		return "AccessModifier()";
	}
}