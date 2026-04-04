#include "ast/leaf/fVarargsExpansion.hpp"

#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::leaf {

	fVarargsExpansion::fVarargsExpansion(const fToken* varargsFirstToken) : varargsFirstToken_(varargsFirstToken){}

	const fToken* fVarargsExpansion::getIdentToken() const{
		return varargsFirstToken_;
	}

	std::string fVarargsExpansion::getIdentName() const {
		return varargsFirstToken_->getTStrVal();
	}

	std::string fVarargsExpansion::toString() const {
		return varargsFirstToken_->toString();
	}

	void fVarargsExpansion::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fVarargsExpansion>(shared_from_this()), s);
	}

}
