#include "ast/leaf/fTypeArgs.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTypeArgs::fTypeArgs(std::vector<sp<fType>> &&typeArgs) : typeArgs_(std::move(typeArgs)) {
		if (this->typeArgs_.empty()) {
			throw std::invalid_argument("Type arguments cannot be empty");
		}
	}

	const std::vector<sp<fType>>& fTypeArgs::getTypeArgs() const {
		return typeArgs_;
	}

	void fTypeArgs::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fTypeArgs>(shared_from_this()), s);
	}

	std::string fTypeArgs::toString() const {
		return "TypeArgs(typeArgs=[" + [&]() {
			std::string result;
			for (const auto& typeArg : typeArgs_) {
				result += (typeArg ? typeArg->toString() : "null") + ", ";
			}
			return result;
		}() + "])";
	}
}