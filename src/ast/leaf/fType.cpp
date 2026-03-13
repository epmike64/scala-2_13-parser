#include "ast/leaf/fType.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fType::fType(sp<fAstProdSubTreeN> &&typeTree) : _typeTree(std::move(typeTree)) {
		if (this->_typeTree == nullptr) {
			throw std::invalid_argument("Type tree cannot be null");
		}
	}

	const sp<fAstProdSubTreeN> &fType::getType() const {
		return _typeTree;
	}


	void fType::accept(std::shared_ptr<fAstNodVisitor> visitor,  esc s) {
		visitor->visit(std::static_pointer_cast<fType>(shared_from_this()), s);
	}

	std::string fType::toString() const {
		return "Type(" + _typeTree->toString() + ")";
	}
}
