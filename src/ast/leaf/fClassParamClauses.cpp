#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fClassParamClauses::setImplicitParams(vector<sp<fClassParam>> &&implicitParams) {
		this->implicitParams_ = std::move(implicitParams);
	}

	void fClassParamClauses::addParams(vector<sp<fClassParam>> &&params) {
		this->classParams_.push_back(std::move(params));
	}

	vector<sp<fClassParam>> fClassParamClauses::getImplicitParams() const {
		return implicitParams_;
	}

	vector<vector<sp<fClassParam>>> fClassParamClauses::getClassParams() const {
		return classParams_;
	}

	void fClassParamClauses::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fClassParamClauses>(shared_from_this()), s);
	}

	std::string fClassParamClauses::toString() const {
		return "fClassParamClauses()";
	}
}