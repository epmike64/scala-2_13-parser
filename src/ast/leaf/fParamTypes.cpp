#include "ast/leaf/fParamTypes.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fParamTypes::fParamTypes(sp<std::vector<sp<fParamType>>> &&paramTypes) : paramTypes_(std::move(paramTypes)) {
		if (this->paramTypes_ == nullptr) {
			throw std::invalid_argument("Parameter types cannot be null");
		}
	}

	sp<std::vector<sp<fParamType>>> fParamTypes::getParamTypes() const {
		return paramTypes_;
	}


	void fParamTypes::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fParamTypes>(shared_from_this()), s);
	}

	std::string fParamTypes::toString() const {
		return "AccessModifier()";
	}
}