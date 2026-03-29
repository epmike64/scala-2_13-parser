#include "ast/leaf/fParamTypes.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fParamType.hpp"

namespace zebra::ast::leaf {

	fParamTypes::fParamTypes(sp<std::vector<sp<fParamType>>> &&paramTypes) : paramTypes_(std::move(paramTypes)) {
		if (this->paramTypes_ == nullptr) {
			throw std::invalid_argument("Parameter types cannot be null");
		}
	}

	sp<std::vector<sp<fParamType>>> fParamTypes::getParamTypes() const {
		return paramTypes_;
	}


	void fParamTypes::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fParamTypes>(shared_from_this()), s);
	}

	std::string fParamTypes::toString() const {
		return "fParamTypes(paramTypes=" + [&]() {
			std::string result = "[";
			for (const auto& paramType : *paramTypes_) {
				result += (paramType ? paramType->toString() : "null") + ", ";
			}
			result += "]";
			return result;
		}() + ")";
	}
}
