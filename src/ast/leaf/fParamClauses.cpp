#include "ast/leaf/fParamClauses.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fParam.hpp"

namespace zebra::ast::leaf {

	void fParamClauses::addParams(vector<sp<fParam>> &&params) {
		this->params_.push_back(std::move(params));
	}

	 void fParamClauses::setImplicitParams(std::vector<sp<fParam>> &&implicitParams) {
		this->implicitParams_ = std::make_shared<vector<sp<fParam>>>(std::move(implicitParams));
	}

	vector<vector<sp<fParam>>> fParamClauses::getParamLists() const {
		return params_;
	}

	sp<vector<sp<fParam>>> fParamClauses::getImplicitParamList() const {
		return implicitParams_;
	}

	void fParamClauses::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fParamClauses>(shared_from_this()), s);
	}

	std::string fParamClauses::toString() const {
		return "ParamClauses(params=" + [&]() {
			std::string result = "[";
			for (const auto& paramList : params_) {
				result += "[";
				for (const auto& param : paramList) {
					result += (param ? param->toString() : "null") + ", ";
				}
				result += "], ";
			}
			result += "]";
			return result;
		}() + ", implicitParams=" + (implicitParams_ ? [&]() {
			std::string result = "[";
			for (const auto& param : *implicitParams_) {
				result += (param ? param->toString() : "null") + ", ";
			}
			result += "]";
			return result;
		}() : "null") + ")";
	}
}
