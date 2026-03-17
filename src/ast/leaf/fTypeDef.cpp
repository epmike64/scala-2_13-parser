#include "ast/leaf/fTypeDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fType.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"

namespace zebra::ast::leaf {

	fTypeDef::fTypeDef(const fToken* typeDefName) : _typeDefName(typeDefName) {
		if (this->_typeDefName == nullptr) {
			throw std::invalid_argument("Type definition name token cannot be null");
		}
	}

	const fToken* fTypeDef::getTypeDefName() const {
		return _typeDefName;
	}

	void fTypeDef::setTypeParams(const sp<std::vector<sp<fVariantTypeParam>>>& typeParams) {
        this->typeParams_ = typeParams;
    }

	sp<std::vector<sp<fVariantTypeParam>>> fTypeDef::getTypeParams() const {
		return typeParams_;
	}

	void fTypeDef::setAssignedType(sp<fType> &&assignedType) {
		this->assignedType_ = std::move(assignedType);
	}

	sp<fType> fTypeDef::getAssignedType() const {
		return assignedType_;
	}


	void fTypeDef::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fTypeDef>(shared_from_this()), s);
	}

	std::string fTypeDef::toString() const {
		std::string typeParamsStr;
		if (typeParams_) {
			for (const auto &tp: *typeParams_) {
				if (!typeParamsStr.empty()) typeParamsStr += ", ";
				typeParamsStr += tp->toString();
			}
		}
		return "TypeDef(name=" + getTypeDefName()->toString() +
		       ", typeParams=[" + (typeParams_? "" : typeParamsStr) +
		       ", assignedType=" + (assignedType_ ? assignedType_->toString() : "null") + ")";
	}
}
