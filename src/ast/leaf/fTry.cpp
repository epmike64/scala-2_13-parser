#include "ast/leaf/fTry.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTry::fTry(sp<fAstProdSubTreeN> &&tryBlock) : tryBlock_(std::move(tryBlock)) {
		if (this->tryBlock_ == nullptr) {
			throw std::invalid_argument("Try block cannot be null");
		}
	}

	void fTry::setCatchBlock(sp<fAstProdSubTreeN> &&catchBlock) {
		this->catchBlock_ = std::move(catchBlock);
	}

	void fTry::setFinallyBlock(sp<fAstProdSubTreeN> &&finallyBlock) {
		this->finallyBlock_ = std::move(finallyBlock);
	}

	sp<fAstProdSubTreeN> fTry::getTryBlock() const {
		return tryBlock_;
	}

	sp<fAstProdSubTreeN> fTry::getCatchBlock() const {
		return catchBlock_;
	}

	sp<fAstProdSubTreeN> fTry::getFinallyBlock() const {
		return finallyBlock_;
	}

	void fTry::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fTry>(shared_from_this()));
	}

	std::string fTry::toString() const {
		return "AccessModifier()";
	}
}