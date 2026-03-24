#include "ast/leaf/fFunSig.hpp"
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


	fFunSig::fFunSig(const fToken *funName) : identName_(funName) {
		if (this->identName_ == nullptr) {
			throw std::invalid_argument("Function name cannot be null");
		}
	}

	void fFunSig::setParamClauses(sp<fParamClauses> &&paramClauses) {
		if (paramClauses == nullptr) {
			throw std::invalid_argument("Parameter clauses cannot be null");
		}
		this->paramClauses_ = std::move(paramClauses);
	}

	void fFunSig::setFunTypeParamClause(std::vector<sp<fTypeParam> > &&typeParam) {
		this->typeParamClause_ = ms<fFunTypeParamClause>(std::move(typeParam));
	}

	const fToken *fFunSig::getIdentToken() const {
		return identName_;
	}

	std::string fFunSig::getIdentName() const {
		return identName_->getTStrVal();
	}

	sp<fParamClauses> fFunSig::getParamClauses() const {
		return paramClauses_;
	}

	sp<fFunTypeParamClause> fFunSig::getFunTypeParamClause() const {
		return typeParamClause_;
	}

	void fFunSig::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fFunSig>(shared_from_this()), s);
	}

	std::string fFunSig::toString() const {
		return "FunSig(name=" + identName_->toString() +
		       ", paramClauses=" + (paramClauses_ ? paramClauses_->toString() : "null") +
		       ", typeParam=" + (typeParamClause_
			                         ? [&]() {
				                         std::string result = "[";
				                         for (const auto &tp: *typeParamClause_) {
					                         result += (tp ? tp->toString() : "null") + ", ";
				                         }
				                         result += "]";
				                         return result;
			                         }()
			                         : "null") + ")";
	}
}
