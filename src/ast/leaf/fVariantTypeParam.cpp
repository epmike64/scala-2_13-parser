#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fVariantTypeParam::setAnnotations(sp<fAnnotations> &&annotations) {
		this->anns_ = std::move(annotations);
	}
	
	sp<fAnnotations> fVariantTypeParam::getAnnotations() const {
		return anns_;
	}

	lex::kind::fVarianceE fVariantTypeParam::getVariance() const {
		return variance_;
	}

	sp<fTypeParam> fVariantTypeParam::getTypeParam() {
		return typeParam_;
	}

	void fVariantTypeParam::setTypeParam(const sp<fTypeParam> &typeParam) {
		typeParam_ = typeParam;
	}

	void fVariantTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fVariantTypeParam>(shared_from_this()), s);
	}

	std::string fVariantTypeParam::toString() const {
		const std::string varianceStr = variance_ == lex::kind::fVarianceE::INVARIANT  ? "invariant" :
		                                variance_ == lex::kind::fVarianceE::COVARIANT   ? "covariant" : "contravariant";
		return "fVariantTypeParam(variance=" + varianceStr + ", typeParam=" + (typeParam_ ? typeParam_->toString() : "null") + ")";
	}
}