#include "ast/leaf/fFunSig.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fFunSig::fFunSig(const fToken* funName) : funName_(funName) {
		if (this->funName_ == nullptr) {
			throw std::invalid_argument("Function name cannot be null");
		}
	}

	void fFunSig::setParamClauses(sp<fParamClauses> &&paramClauses) {
		if (paramClauses == nullptr) {
			throw std::invalid_argument("Parameter clauses cannot be null");
		}
		this->paramClauses_ = std::move(paramClauses);
	}

	void fFunSig::setTypeParams(std::vector<sp<fTypeParam> >  &&typeParam) {
		this->typeParam_ = std::make_shared<std::vector<sp<fTypeParam>>>(std::move(typeParam));
	}

	const fToken* fFunSig::getFunName() const {
		return funName_;
	}

	sp<fParamClauses> fFunSig::getParamClauses() const {
		return paramClauses_;
	}

	sp<std::vector<sp<fTypeParam>>> fFunSig::getTypeParam() const {
		return typeParam_;
	}

	void fFunSig::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fFunSig>(shared_from_this()), s);
	}

	std::string fFunSig::toString() const {
		return "fFunSig()";
	}
}