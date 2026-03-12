#include "ast/tree/fLangAstTree.hpp"

namespace zebra::ast::tree {
	void fBinary::setLeft(sp<fAstOprndNod> left) {
		left_ = left;
	}

	void fBinary::setRight(sp<fAstOprndNod> right) {
		right_ = right;
	}

	void fBinary::setOptr(sp<fAstOptrNod> optr) {
		optr_ = optr;
	}

	sp<fAstOptrNod> fBinary::getOperator() const {
		return optr_;
	}

	sp<fAstOprndNod> fBinary::getLeft() const {
		return left_;
	}

	sp<fAstOprndNod> fBinary::getRight() const {
		return right_;
	}

	std::string fBinary::toString() const {
		std::ostringstream oss;
		oss << "fBinary(";
		if (optr_ != nullptr) {
			oss << "operator=" << optr_->toString() << ", ";
		}
		if (left_ != nullptr) {
			oss << "left=" << left_->toString() << ", ";
		}
		if (right_ != nullptr) {
			oss << "right=" << right_->toString();
		}
		oss << ")";
		return oss.str();
	}
};
