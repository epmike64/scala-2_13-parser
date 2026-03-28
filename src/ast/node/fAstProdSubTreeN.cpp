#include "ast/node/fAstProdSubTreeN.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::node {

	void fAstProdSubTreeN::accept(sp<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fAstProdSubTreeN>(shared_from_this()), s);
	}

	std::string fAstProdSubTreeN::toString() const
	{
		std::string topNodeStr;
		if (rootOpNod && rootOpNod->getAstRightN()) {
			topNodeStr = rootOpNod->getAstRightN()->toString();
		}
		return "AstProdSubTreeN(" + to_gr_prod_string(gp) + ", root->right: " + topNodeStr + ")";
	}

} // namespace zebra::ast::node

