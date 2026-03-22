#include "back/tree/ZVisitHelp.hpp"

#include "ast/symbol/ZEnclScope.hpp"

namespace zebra::back::tree {
	ast::symbol::esc ZVisitHelp::getWrapScope(ast::symbol::esc prnSc, ast::symbol::ZLangConstruct lc) {
		assert(prnSc != nullptr);
		while (prnSc->getLangConstruct() != lc) {
			prnSc = prnSc->getParentScope();
			if (prnSc == nullptr) {
				throw std::runtime_error("No enclosing scope found for language construct: " + std::to_string(lc));
			}
		}
		return prnSc;
	}
}
