#include "ast/leaf/fGenerator.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fGenerator::fGenerator(sp<fAstProdSubTreeN> &&casePattern1, bool isCase) : casePattern1_(std::move(casePattern1)), isCase(isCase) {
		if (this->casePattern1_ == nullptr) {
			throw std::invalid_argument("Case pattern cannot be null");
		}
	}

	void fGenerator::addGuard(sp<fAstProdSubTreeN> &&guard) {
		if (guard == nullptr) {
			throw std::invalid_argument("Guard cannot be null");
		}
		this->guards_.push_back(std::move(guard));
	}

	void fGenerator::setInExpr(sp<fAstProdSubTreeN> &&inExpr) {
		if (inExpr == nullptr) {
			throw std::invalid_argument("In expression cannot be null");
		}
		this->inExpr_ = std::move(inExpr);
	}

	void fGenerator::addEndingPattern1(sp<fAstProdSubTreeN> &&endingPattern1) {
		if (endingPattern1 == nullptr) {
			throw std::invalid_argument("Ending pattern cannot be null");
		}
		this->endingPattern1s_.push_back(std::move(endingPattern1));
	}

	void fGenerator::addEndingExpr(sp<fAstProdSubTreeN> &&endingExpr) {
		if (endingExpr == nullptr) {
			throw std::invalid_argument("Ending expression cannot be null");
		}
		this->endingExprs_.push_back(std::move(endingExpr));
	}

	sp<fAstProdSubTreeN> fGenerator::getCasePattern1() const {
		return casePattern1_;
	}

	bool fGenerator::isCaseGenerator() const {
		return isCase;
	}

	std::vector<sp<fAstProdSubTreeN>> fGenerator::getGuards() const {
		return guards_;
	}

	sp<fAstProdSubTreeN> fGenerator::getInExpr() const {
		return inExpr_;
	}

	std::vector<sp<fAstProdSubTreeN>> fGenerator::getEndingPattern1s() const {
		return endingPattern1s_;
	}

	std::vector<sp<fAstProdSubTreeN>> fGenerator::getEndingExprs() const {
		return endingExprs_;
	}


	void fGenerator::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fGenerator>(shared_from_this()));
	}

	std::string fGenerator::toString() const {
		return "AccessModifier()";
	}
}