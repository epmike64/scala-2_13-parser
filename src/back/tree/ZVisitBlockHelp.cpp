#include "back/tree/ZVisitBlockHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZSymbol.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;


	void ZVisitBlockHelp::visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Block" << std::endl;

		sp<ZBlock> block = ms<ZBlock>();
		 esc blockScp = ms<ZEnclScope>(prnSc, block);

		for (const auto& stmt : n->getStmts()) {
			stmt->accept(visitor, blockScp);
		}
	}

}
