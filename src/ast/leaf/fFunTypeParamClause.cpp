
#include "ast/leaf/fFunTypeParamClause.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include <string>
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fTypeParam.hpp"

namespace zebra::ast::leaf {

	fFunTypeParamClause::fFunTypeParamClause(std::vector<sp<fTypeParam> > typeParam) {
		this->typeParams_ = std::move(typeParam);
	}

	const std::vector<sp<fTypeParam> > &fFunTypeParamClause::getTypeParamList() {
		return typeParams_;
	}

	void fFunTypeParamClause::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fFunTypeParamClause>(shared_from_this()), s);
	}

	std::string fFunTypeParamClause::toString() const {
		return "FunTypeParamClause(typeParams=" + [&]() {
			std::string result = "[";
			for (const auto &tp: typeParams_) {
				result += (tp ? tp->toString() : "null") + ", ";
			}
			result += "]";
			return result;
		}() + ")";
	}
}