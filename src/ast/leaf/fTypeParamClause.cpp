
#include "ast/leaf/fTypeParamClause.hpp"

#include "ast/leaf/fVariantTypeParam.hpp"

namespace zebra::ast::leaf {


	fTypeParamClause::fTypeParamClause(sp<std::vector<sp<fVariantTypeParam> > > variantTypeParams) {
		if (variantTypeParams == nullptr) {
			throw std::invalid_argument("Variant type parameters cannot be null");
		}
		this->variantTypeParams_ = std::move(variantTypeParams);
	}

	sp<std::vector<sp<fVariantTypeParam>>> fTypeParamClause::getVariantTypeParams() const {
		return variantTypeParams_;
	}

	void fTypeParamClause::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fTypeParamClause>(shared_from_this()), s);
	}

	std::string fTypeParamClause::toString() const {
		std::string result = "fTypeParamClause(variantTypeParams=[";
		if (variantTypeParams_ != nullptr) {
			for (const auto& param : *variantTypeParams_) {
				result += param->toString() + ", ";
			}
		}
		result += "])";
		return result;
	}
}
