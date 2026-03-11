#include "ast/leaf/fFor.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {


	fFor::fFor(std::vector<sp<fGenerator>> generators): generators_(std::move(generators)) {
		if (this->generators_.empty()) {
			throw std::invalid_argument("Generators cannot be empty");
		}
	}

	const std::vector<sp<fGenerator>> &fFor::getGenerators() const {
		return generators_;
	}

	void fFor::setYield(bool isYield) {
		this->isYield_ = isYield;
	}

	bool fFor::isYield() const {
		return isYield_;
	}

	void fFor::setYieldExpr(sp<fAstProdSubTreeN> &&yieldExpr) {
		if (yieldExpr == nullptr) {
			throw std::invalid_argument("Yield expression cannot be null");
		}
		this->yieldExpr_ = std::move(yieldExpr);
	}

	sp<fAstProdSubTreeN> fFor::getYieldExpr() const {
		return yieldExpr_;
	}


	void fFor::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fFor>(shared_from_this()));
	}

	std::string fFor::toString() const {
		return "AccessModifier()";
	}
}