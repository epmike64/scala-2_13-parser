

#include "ast/node/fAstOptrNod.hpp"
#include "ast/node/fAstNodKndE.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fLangOperatorKind.hpp"
#include "lex/token/fToken.hpp"

namespace zebra::ast::node {

	using lex::kind::fLangOperatorKind;
	using lex::token::fToken;

	fAstOptrNod::fAstOptrNod(const fLangOperatorKind* kind, const fToken* operatorToken)
		: operatorKind_(kind), operatorToken_(operatorToken) {
	}
	const fLangOperatorKind* fAstOptrNod::getLangOptrKnd()  {
		return operatorKind_;
	}
	bool fAstOptrNod::isOperator()  {
		return true;
	}
	fAstNodKndE fAstOptrNod::astNKndE() {
		return fAstNodKndE::AST_OPERATOR;
	}
	void fAstOptrNod::setAstLeftN(std::shared_ptr<fAstNod> astLeftN) {
		this->astLeftN_ = astLeftN;
		astLeftN->setAstParentN(shared_from_this());
	}

	void fAstOptrNod::setAstRightN(std::shared_ptr<fAstNod> astRightN) {
		this->astRightN_ = astRightN;
		astRightN->setAstParentN(shared_from_this());
	}

	void fAstOptrNod::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fAstOptrNod>(shared_from_this()), s);
	}

	std::string fAstOptrNod::toString() const {
		std::string leftStr = (astLeftN_ != nullptr) ? astLeftN_->toString() : "null";
		std::string rightStr = (astRightN_ != nullptr) ? astRightN_->toString() : "null";
		return "AstOptrNod(" + operatorToken_->toString() + ",  opKind: " + operatorKind_->toString() + ", left: " + leftStr + ", right: " + rightStr + ")";
	}
}
