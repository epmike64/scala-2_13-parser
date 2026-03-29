#include "ast/leaf/fThisFunc.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fConstrBlock.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fParamClauses.hpp"

namespace zebra::ast::leaf {

	fThisFunc::fThisFunc(sp<fModifiers> &&modifiers) : fFunc(std::move(modifiers)) {}

	sp<fConstrBlock> fThisFunc::getConstrBlock() const {
		return constrBlock;
	}

	 sp<fParamClauses> fThisFunc::getParamClauses() const {
		return clauses;
	}

	 void fThisFunc::setConstrBlock(sp<fConstrBlock> &&constrBlock) {
		this->constrBlock = std::move(constrBlock);
	}

	 void fThisFunc::setParamClauses(sp<fParamClauses> &&clauses) {
		this->clauses = std::move(clauses);
	}

	void fThisFunc::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fThisFunc>(shared_from_this()), s);
	}

	std::string fThisFunc::toString() const {
		return "fThisFun(modifiers=" + (getModifiers() ? getModifiers()->toString() : "null") +
		       ", constrBlock=" + (constrBlock ? constrBlock->toString() : "null") +
		       ", paramClauses=" + (clauses ? clauses->toString() : "null") + ")";
	}
}
