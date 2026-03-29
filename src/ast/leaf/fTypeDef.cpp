#include "ast/leaf/fTypeDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "ast/leaf/fTypeParamClause.hpp"

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

	void fTypeDef::setTypeParams(sp<fTypeParamClause> typeParams) {
        this->typeParamClause_ = typeParams;
    }

	sp<fTypeParamClause> fTypeDef::getTypeParams() const {
		return typeParamClause_;
	}

	void fTypeDef::setAssignedType(sp<fType> &&assignedType) {
		this->assignedType_ = std::move(assignedType);
	}

	sp<fType> fTypeDef::getAssignedType() const {
		return assignedType_;
	}


	void fTypeDef::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fTypeDef>(shared_from_this()), s);
	}

	std::string fTypeDef::toString() const {
		return "TypeDef(name=" + getTypeDefName()->toString() +
		       ", typeParams=[" + ((typeParamClause_? "" : typeParamClause_->toString())) +
		       ", assignedType=" + (assignedType_ ? assignedType_->toString() : "null") + ")";
	}
}
