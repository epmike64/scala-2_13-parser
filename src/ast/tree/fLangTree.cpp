#include "ast/tree/fLangTree.hpp"

namespace zebra::ast::tree {

	fLangTrBranch::fLangTrBranch(const sp<fAstOprndNod> &left){
		if (left == nullptr) {
			throw std::runtime_error("fLangTrBranch::fLangTrBranch: left operand is null");
		}
		astLeftN_ = left;
	}

	void fLangTrBranch::setRight(sp<fAstOprndNod> right) {
		if (right == nullptr) {
			throw std::runtime_error("fLangTrBranch::setRight: right operand is null");
		}
		astRightN_ = right;
	}

	void fLangTrBranch::setOptr(sp<fAstOptrNod> optr) {
		if (optr == nullptr) {
			throw std::runtime_error("fLangTrBranch::setOptr: optr is null");
		}
		astParentN_ = optr;
	}

	sp<fAstOptrNod> fLangTrBranch::getOperator() const {
		return std::dynamic_pointer_cast<fAstOptrNod>(fAstNod::astParentN_);
	}

	sp<fAstOprndNod> fLangTrBranch::getLeft() const {
		return std::dynamic_pointer_cast<fAstOprndNod>(astLeftN_);
	}

	sp<fAstOprndNod> fLangTrBranch::getRight() const {
		return std::dynamic_pointer_cast<fAstOprndNod>(astRightN_);
	}

	std::string fLangTrBranch::toString() const {
		std::ostringstream oss;
		oss << "fBinary(";

		if (getOperator()) {
			oss << "operator=" << getOperator()->toString() << ", ";
		}
		if (getLeft()) {
			oss << "left=" << getLeft()->toString() << ", ";
		}
		if (getRight()) {
			oss << "right=" << getRight()->toString();
		}

		oss << ")";
		return oss.str();
	}
};
