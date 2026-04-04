#include "ast/leaf/fConstrBlock.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fConstrBlock::addBlockStmt(sp<fAstNod> && stmt) {
		if (stmt == nullptr) {
			throw std::invalid_argument("Block statement cannot be null");
		}
		if (!blockStmts_) {
			blockStmts_ = ms<std::vector<std::shared_ptr<fAstNod>>>();
		}
		blockStmts_->push_back(std::move(stmt));
	}

	void fConstrBlock::addArgExprs(sp<fAstProdSubTreeN> && expr) {
		if (expr == nullptr) {
			throw std::invalid_argument("Argument expression cannot be null");
		}
		if (!argExprs_) {
			argExprs_ = ms<std::vector<std::shared_ptr<fAstProdSubTreeN>>>();
		}
		argExprs_->push_back(std::move(expr));
	}

	PVecP<fAstNod> fConstrBlock::getBlockStmts() {
		return blockStmts_;
	}

	PVecP<fAstProdSubTreeN> fConstrBlock::getArgExprs() {
		return argExprs_;
	}

	void fConstrBlock::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fConstrBlock>(shared_from_this()), s);
	}

	std::string fConstrBlock::toString() const {
		return "fConstrBlock";
	}
}