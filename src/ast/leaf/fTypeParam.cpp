#include "ast/leaf/fTypeParam.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fType.hpp"

namespace zebra::ast::leaf {


	void fTypeParam::setTypeParamName(const fToken* typeParamName) {
		this->typeParamName_ = typeParamName;
	}

	const fToken* fTypeParam::getTypeParamName() const {
		return typeParamName_;
	}

	void fTypeParam::setVariantTypeParam(std::vector<sp<fVariantTypeParam>> &&variantTypeParam) {
        this->variantTypeParams_  = std::make_shared<std::vector<sp<fVariantTypeParam>>>(std::move(variantTypeParam));
    }

	void fTypeParam::setVariantTypeParams(const sp<std::vector<sp<fVariantTypeParam>>>& variantTypeParams) {
		this->variantTypeParams_ = variantTypeParams;
	}

	sp<std::vector<sp<fVariantTypeParam>>> fTypeParam::getVariantTypeParam() const {
        return variantTypeParams_;
    }


	void fTypeParam::addType(sp<fType> &&types) {
        if (!types) {
            throw std::invalid_argument("Type added to type parameter cannot be null");
        }
        if (!types_) {
            types_ = std::make_shared<std::vector<sp<fType>>>();
        }
        this->types_->push_back(std::move(types));
    }

	sp<std::vector<sp<fType>>> fTypeParam::getTypes() const {
        return types_;
    }

	void fTypeParam::addContextBound(sp<fType> &&contextBound) {
        if (!contextBound) {
            throw std::invalid_argument("Context bound added to type parameter cannot be null");
        }
        if (!contextBounds_) {
            contextBounds_ = std::make_shared<std::vector<sp<fType>>>();
        }
        this->contextBounds_->push_back(std::move(contextBound));
    }

	sp<std::vector<sp<fType>>> fTypeParam::getContextBounds() const {
        return contextBounds_;
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


	void fTypeParam::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fTypeParam>(shared_from_this()), s);
	}

	std::string fTypeParam::toString() const {
		return "TypeParam(name=" + (typeParamName_ ? typeParamName_->toString() : "null") +
		       ", variantTypeParams=" + (variantTypeParams_ ? std::to_string(variantTypeParams_->size()) : "null") +
		       ", upperBound=" + (upperBound_ ? upperBound_->toString() : "null") +
		       ", lowerBound=" + (lowerBound_ ? lowerBound_->toString() : "null") +
		       ", types=" + (types_ ? std::to_string(types_->size()) : "null") +
		       ", contextBounds=" + (contextBounds_ ? std::to_string(contextBounds_->size()) : "null") + ")";
	}
}
