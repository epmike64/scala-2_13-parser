#include "ast/leaf/fSelfType.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {

	 fSelfType::fSelfType(const lex::token::fToken &selfToken) : selfToken_(selfToken) {}

	void fSelfType::setSelfType(sp<fType> &&selfType) {
		this->selfType_ = std::move(selfType);
	}

	sp<fType> fSelfType::getSelfType()  {
		return selfType_;
	}

	void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s)  {
		visitor->visit(std::static_pointer_cast<fSelfType>(shared_from_this()), s);
	}

	std::string fSelfType::toString() const {
		return "SelfType(selfToken=" + selfToken_.toString() + ", selfType=" + (selfType_ ? selfType_->toString() : "null") + ")";
	 }
}
