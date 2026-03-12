#include "ast/leaf/fCaseClause.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {


	fCaseClause::fCaseClause(sp<fAstProdSubTreeN> &&pattern) : pattern(std::move(pattern)) {
		if (this->pattern == nullptr) {
			throw std::invalid_argument("Pattern cannot be null");
		}
	}



	sp<fAstProdSubTreeN> fCaseClause::getPattern() const {
		return pattern;
	}

	sp<fAstProdSubTreeN> fCaseClause::getGuard() const {
		return guard;
	}

	sp<fBlock> fCaseClause::getBlock() const {
		return block;
	}

	void fCaseClause::setGuard(sp<fAstProdSubTreeN> &&guard) {
		this->guard = std::move(guard);
	}

	void fCaseClause::setBlock(sp<fBlock> &&block) {
		this->block = std::move(block);
	}

	void fCaseClause::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fCaseClause>(shared_from_this()));
	}

	std::string fCaseClause::toString() const {
		return "fCaseClause()";
	}
}