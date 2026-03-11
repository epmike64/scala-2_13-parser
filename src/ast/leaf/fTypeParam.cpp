#include "ast/leaf/fTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTypeParam::fTypeParam(const fToken* name) : typeParamName_(name) {
		if (this->typeParamName_ == nullptr) {
			throw std::invalid_argument("Type parameter name token cannot be null");
		}
	}

	const fToken* fTypeParam::getTypeParamName() const {
		return typeParamName_;
	}

	void fTypeParam::setVariantTypeParam(std::vector<sp<fVariantTypeParam>> &&variantTypeParam) {
        this->variantTypeParam_  = std::make_shared<std::vector<sp<fVariantTypeParam>>>(std::move(variantTypeParam));
    }

	void fTypeParam::setVariantTypeParams(std::vector<sp<fVariantTypeParam>> &&variantTypeParams) {
		this->variantTypeParam_ = std::make_shared<std::vector<sp<fVariantTypeParam>>>(std::move(variantTypeParams));
	}

	sp<std::vector<sp<fVariantTypeParam>>> fTypeParam::getVariantTypeParam() const {
        return variantTypeParam_;
    }



	void fTypeParam::setType(sp<fType> &&type) {
		this->type_ = std::move(type);
	}

	sp<fType> fTypeParam::getType() const {
		return type_;
	}

	void fTypeParam::setUpperBound(sp<fType> &&upperBound) {
		this->upperBound_ = std::move(upperBound);
	}

	sp<fType> fTypeParam::getUpperBound() const {
		return upperBound_;
	}

	void fTypeParam::setLowerBound(sp<fType> &&lowerBound) {
		this->lowerBound_ = std::move(lowerBound);
	}

	sp<fType> fTypeParam::getLowerBound() const {
		return lowerBound_;
	}


	void fTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fTypeParam>(shared_from_this()));
	}

	std::string fTypeParam::toString() const {
		return "AccessModifier()";
	}
}