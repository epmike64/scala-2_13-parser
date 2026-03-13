#include "ast/leaf/fParamType.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fParamType::fParamType(sp<fType> &&type, bool isFatArrow, bool isStar)
		: fType(sp<fAstProdSubTreeN>(type->getType())), isFatArrow(isFatArrow), isStar(isStar) {}


	void fParamType::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fParamType>(shared_from_this()), s);
	}

	std::string fParamType::toString() const {
		return "AccessModifier()";
	}
}