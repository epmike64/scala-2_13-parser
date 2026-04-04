#include "ast/leaf/fSelfType.hpp"


namespace zebra::ast::leaf {

	 fSelfType::fSelfType(const fToken* selfToken) : identName_(selfToken) {}

	void fSelfType::setSelfType(sp<fType> &&selfType) {
		this->selfType_ = std::move(selfType);
	}

	sp<fType> fSelfType::getSelfType()  {
		return selfType_;
	}

	void fSelfType::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s)  {
		visitor->visit(std::static_pointer_cast<fSelfType>(shared_from_this()), s);
	}

	const fToken* fSelfType::getIdentToken() const {
		return identName_;
	}

	const std::string& fSelfType::getIdentName() const {
		 return identName_->getTStrVal();
	 }

	std::string fSelfType::toString() const {
		return "SelfType(selfToken=" + identName_->toString() + ", selfType=" + (selfType_ ? selfType_->toString() : "null") + ")";
	 }
}
