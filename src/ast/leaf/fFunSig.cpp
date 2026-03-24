#include "ast/leaf/fFunSig.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fTypeParam.hpp"

namespace zebra::ast::leaf {

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
		this->funTypeParamClause_ = ms<fFunTypeParamClause>(std::move(typeParam));
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
		return funTypeParamClause_;
	}

	void fFunSig::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fFunSig>(shared_from_this()), s);
	}

	std::string fFunSig::toString() const {
		return "FunSig(name=" + (identName_ ? identName_->toString() : "null") +
		       ", paramClauses=" + (paramClauses_ ? paramClauses_->toString() : "null") +
		       ", funTypeParamClause=" + (funTypeParamClause_ ? funTypeParamClause_->toString() : "null") + ")";
	}
}
