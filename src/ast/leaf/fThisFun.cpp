#include "ast/leaf/fThisFun.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fThisFun::fThisFun(sp<fModifiers> &&modifiers) : fFun(std::move(modifiers)) {}

	sp<fConstrBlock> fThisFun::getConstrBlock() const {
		return constrBlock;
	}

	 sp<fParamClauses> fThisFun::getParamClauses() const {
		return clauses;
	}

	 void fThisFun::setConstrBlock(sp<fConstrBlock> &&constrBlock) {
		this->constrBlock = std::move(constrBlock);
	}

	 void fThisFun::setParamClauses(sp<fParamClauses> &&clauses) {
		this->clauses = std::move(clauses);
	}

	void fThisFun::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fThisFun>(shared_from_this()));
	}

	std::string fThisFun::toString() const {
		return "AccessModifier()";
	}
}