#include "back/tree/ZVisitStmtHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;


	void ZVisitStmtHelp::visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Block" << std::endl;
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(visitor, prnSc);
		}
	}

}
