#include "ast/node/fAstProdSubTreeN.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::node {

	void fAstProdSubTreeN::accept(sp<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fAstProdSubTreeN>(shared_from_this()), s);
	}

	std::string fAstProdSubTreeN::toString() const
	{
		return "AstProdSubTreeN(" + to_gr_prod_string(gp) + ")";
	}

} // namespace zebra::ast::node

