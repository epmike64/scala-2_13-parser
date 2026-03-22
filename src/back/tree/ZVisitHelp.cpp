#include "back/tree/ZVisitHelp.hpp"

#include "ast/symbol/ZEnclScope.hpp"
#include "iostream"
namespace zebra::back::tree {
	using namespace ast::symbol;

	esc ZVisitHelp::getWrapScope(esc prnSc, ZLangConstruct lc) {
		assert(prnSc != nullptr);
		while (prnSc->getLangConstruct() != lc) {
			prnSc = prnSc->getParentScope();
			if (prnSc == nullptr) {
				throw std::runtime_error("No enclosing scope found for language construct: " + std::to_string(lc));
			}
		}
		return prnSc;
	}

	void ZVisitHelp::treePostOrderPush(sp<fAstNod> n, esc prnSc) {
		sp<ZProdSubTreeN> prnt = std::dynamic_pointer_cast<ZProdSubTreeN>(prnSc->getZSymbol());
		if (prnt) {
			prnt->getTreePostOrderSS()->push_back(n);
			std::cout << "Pushed: " + n->toString() << std::endl;
			std::cout << prnt->getTreePostOrderSS()->toString() << std::endl;
			std::cout <<  "" << std::endl;
		} else {
			std::cout << "" << std::endl;
		}
	}
}
