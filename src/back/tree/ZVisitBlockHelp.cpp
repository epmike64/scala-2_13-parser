#include "back/tree/ZVisitBlockHelp.hpp"

#include <iostream>

#include "ast/leaf/fBlock.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZSymbol.hpp"
#include "util/fUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;
	using namespace ast;

	// void ZVisitBlockHelp::visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor) {
	// 	std::cout << "Visiting Block" << std::endl;
	//
	// 	sp<ZBlock> block = ms<ZBlock>();
	// 	 esc blockScp = ms<ZEnclScope>(prnSc, block);
	//
	// 	for (const auto& stmt : n->getStmts()) {
	// 		zaccert(!stmt->isOperator(), "Statements in a block should not be operators");
	// 		switch (dynSp<fLangOprnd>(stmt)->getLangOprndType()) {
	// 			case LOprndT::PROD_SUB_TREE_N: {
	// 				sp<ZProdSubTreeN> pSubTr = ms<ZProdSubTreeN>();
	// 				block->addStmt(pSubTr);
	// 				esc pSubTrScp = ms<ZEnclScope>(blockScp, pSubTr);
	// 				stmt->accept(visitor, pSubTrScp);
	// 				continue;
	// 			}
	// 			default:
	// 				break;
	// 		}
	// 		stmt->accept(visitor, blockScp);
	// 	}
	// }

}
