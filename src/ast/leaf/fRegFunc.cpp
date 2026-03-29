#include "ast/leaf/fRegFunc.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::leaf {

	fRegFunc::fRegFunc(sp<fModifiers> &&modifiers, sp<fFunSig> &&funSig) : fFunc(std::move(modifiers)), funSig_(std::move(funSig)) {
		if (this->funSig_ == nullptr) {
			throw std::invalid_argument("Function signature cannot be null");
		}
	}

	sp<fFunSig> fRegFunc::getFunSig() const {
		return funSig_;
	}

	sp<fType> fRegFunc::getReturnType() const {
		return returnType_;
	}

	void fRegFunc::setReturnType(sp<fType> &&returnType) {
		if (returnType == nullptr) {
			throw std::invalid_argument("Return type cannot be null");
		}
		this->returnType_ = std::move(returnType);
	}

	void  fRegFunc::setFunBodyExpr(sp<fAstProdSubTreeN> &&funBodyExpr) {
		funBodyExpr_ = funBodyExpr;
	}

	sp<fAstProdSubTreeN> fRegFunc::getFunBodyExpr() {
		return funBodyExpr_;
	}

	void  fRegFunc::setFunBodyBlock(sp<fBlock> &&funBodyBlock) {
		funBodyBlock_ = funBodyBlock;
	}

	sp<fBlock> fRegFunc::getFunBodyBlock() {
		return funBodyBlock_;
	}

	void fRegFunc::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fRegFunc>(shared_from_this()), s);
	}

	std::string fRegFunc::toString() const {
		return "fNamedFun(modifiers=" + (getModifiers() ? getModifiers()->toString() : "null") +
		       ", funSig=" + (funSig_ ? funSig_->toString() : "null") +
		       ", returnType=" + (returnType_ ? returnType_->toString() : "null") +
		       ", funBody=" + (funBodyBlock_ ? funBodyBlock_->toString() : (funBodyExpr_ ? funBodyExpr_->toString() : "null")) + ")";
	}
}
