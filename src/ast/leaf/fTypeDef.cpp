#include "ast/leaf/fTypeDef.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTypeDef::fTypeDef(const fToken* typeDefName) : _typeDefName(typeDefName) {
		if (this->_typeDefName == nullptr) {
			throw std::invalid_argument("Type definition name token cannot be null");
		}
	}

	const fToken* fTypeDef::getTypeDefName() const {
		return _typeDefName;
	}

	void fTypeDef::setTypeParams(std::vector<sp<fVariantTypeParam>> &&typeParams) {
        this->typeParams_ = std::move(typeParams);
    }

	std::vector<sp<fVariantTypeParam>> fTypeDef::getTypeParams() const {
		return typeParams_;
	}

	void fTypeDef::setAssignedType(sp<fType> &&assignedType) {
		this->assignedType_ = std::move(assignedType);
	}

	sp<fType> fTypeDef::getAssignedType() const {
		return assignedType_;
	}


	void fTypeDef::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fTypeDef>(shared_from_this()));
	}

	std::string fTypeDef::toString() const {
		return "AccessModifier()";
	}
}