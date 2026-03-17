#include "ast/leaf/fClassParamClauses.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fClassParam.hpp"

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
		std::stringstream out;
		out << "ClassParamClauses(implicitParams=[";
		for (const auto& param : implicitParams_) {
			out << (param ? param->toString() : "null") << ", ";
		}
		out << "], classParams=[";
		for (const auto& paramClauseList : classParams_) {
			out << "[";
			for (const auto& param : paramClauseList) {
				out << (param ? param->toString() : "null") << ", ";
			}
			out << "], ";
		}
		out << "])";
		return out.str();
	}
}
