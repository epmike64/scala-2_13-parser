#include "ast/leaf/fNamedFun.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::leaf {

	fNamedFun::fNamedFun(sp<fModifiers> &&modifiers, sp<fFunSig> &&funSig) : fFun(std::move(modifiers)), funSig_(std::move(funSig)) {
		if (this->funSig_ == nullptr) {
			throw std::invalid_argument("Function signature cannot be null");
		}
	}

	sp<fFunSig> fNamedFun::getFunSig() const {
		return funSig_;
	}

	sp<fType> fNamedFun::getReturnType() const {
		return returnType_;
	}

	sp<fAstOprndNod> fNamedFun::getFunBody() const {
		return funBody_;
	}

	void fNamedFun::setReturnType(sp<fType> &&returnType) {
		if (returnType == nullptr) {
			throw std::invalid_argument("Return type cannot be null");
		}
		this->returnType_ = std::move(returnType);
	}

	void fNamedFun::setFunBody(sp<fAstOprndNod> &&funBody) {
		this->funBody_ = std::move(funBody);
	}


	void fNamedFun::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fNamedFun>(shared_from_this()), s);
	}

	std::string fNamedFun::toString() const {
		return "fNamedFun(modifiers=" + (getModifiers() ? getModifiers()->toString() : "null") +
		       ", funSig=" + (funSig_ ? funSig_->toString() : "null") +
		       ", returnType=" + (returnType_ ? returnType_->toString() : "null") +
		       ", funBody=" + (funBody_ ? funBody_->toString() : "null") + ")";
	}
}
