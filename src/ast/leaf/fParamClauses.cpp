#include "ast/leaf/fParamClauses.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fParamClauses::addParams(vector<sp<fParam>> &&params) {
		this->params_.push_back(std::move(params));
	}

	 void fParamClauses::setImplicitParams(std::vector<sp<fParam>> &&implicitParams) {
		this->implicitParams_ = std::make_shared<vector<sp<fParam>>>(std::move(implicitParams));
	}

	vector<vector<sp<fParam>>> fParamClauses::getParams() const {
		return params_;
	}

	sp<vector<sp<fParam>>> fParamClauses::getImplicitParams() const {
		return implicitParams_;
	}

	void fParamClauses::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fParamClauses>(shared_from_this()));
	}

	std::string fParamClauses::toString() const {
		return "AccessModifier()";
	}
}