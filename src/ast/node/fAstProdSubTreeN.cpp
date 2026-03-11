#include "ast/node/fAstProdSubTreeN.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::ast::node {

	void fAstProdSubTreeN::accept(sp<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fAstProdSubTreeN>(shared_from_this()));
	}

	std::string fAstProdSubTreeN::toString() const
	{
		return "AstProdSubTreeN(" + to_gr_prod_string(gp) + ")";
	}

} // namespace zebra::ast::node

