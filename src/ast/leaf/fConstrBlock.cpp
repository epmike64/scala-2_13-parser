#include "ast/leaf/fConstrBlock.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fConstrBlock::setArgExprs(sp<fAstProdSubTreeN> &&argExprs) {
		if (argExprs == nullptr) {
			throw std::invalid_argument("Argument expressions cannot be null");
		}
		this->argExprs_ = std::move(argExprs);
	}

	void fConstrBlock::addBlockStmt(sp<fAstOprndNod> && stmt) {
		if (stmt == nullptr) {
			throw std::invalid_argument("Block statement cannot be null");
		}
		this->blockStmts_.push_back(std::move(stmt));
	}

	sp<fAstProdSubTreeN> fConstrBlock::getArgExprs() const {
		return argExprs_;
	}

	std::vector<sp<fAstNod>>& fConstrBlock::getBlockStmts() {
		return blockStmts_;
	}


	void fConstrBlock::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fConstrBlock>(shared_from_this()), s);
	}

	std::string fConstrBlock::toString() const {
		return "fConstrBlock";
	}
}