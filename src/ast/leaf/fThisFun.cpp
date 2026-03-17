#include "ast/leaf/fThisFun.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fConstrBlock.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamClauses.hpp"

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

	void fThisFun::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fThisFun>(shared_from_this()), s);
	}

	std::string fThisFun::toString() const {
		return "fThisFun(modifiers=" + (getModifiers() ? getModifiers()->toString() : "null") +
		       ", constrBlock=" + (constrBlock ? constrBlock->toString() : "null") +
		       ", paramClauses=" + (clauses ? clauses->toString() : "null") + ")";
	}
}
