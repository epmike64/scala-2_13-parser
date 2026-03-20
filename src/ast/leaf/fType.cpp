#include "ast/leaf/fType.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fType::fType(sp<fAstProdSubTreeN> &&typeTree) : typeTree_(std::move(typeTree)) {
		if (this->typeTree_ == nullptr) {
			throw std::invalid_argument("Type tree cannot be null");
		}
	}

	const sp<fAstProdSubTreeN> &fType::getTypeTree() const {
		return typeTree_;
	}


	void fType::accept(std::shared_ptr<fAstNodVisitor> visitor,  esc s) {
		visitor->visit(std::static_pointer_cast<fType>(shared_from_this()), s);
	}

	std::string fType::toString() const {
		return "Type(" + typeTree_->toString() + ")";
	}
}
