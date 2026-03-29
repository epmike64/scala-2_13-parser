#pragma once

#include <type_traits>
#include "ast/fLangOperand.hpp"
#include "ast/symbol/ZSymbolBox.hpp"
#include "ast/symbol/ZSymbol.hpp"
#include "ast/symbol/ZEnclScopeFwd.hpp"
#include "ast/node/fAstNodVisitor.hpp"
namespace zebra::back::tree {

	/**
		 * Creates a child ZEnclScope under prnSc, calls accept() on the node,
		 * and returns the new scope so the caller can retrieve the produced ZSymbol.
		 * T must be a subclass of fLangOprnd.
		 */
	template<typename T>
	static sbx visitChildNode(sp<T> node, sp<fAstNodVisitor> visitor) {
		static_assert(std::is_base_of_v<ast::fLangOprnd, T>,
						  "visitChildNode: T must be derived from fLangOprnd");
		sbx symSc = ms<ZSymbolBox>();
		node->accept(visitor, symSc);
		return symSc;
	}

	/**
 * Asserts the scope has no symbol yet, creates a ZSymbol subclass (forwarding
 * any constructor arguments), registers it on prnSc, and returns it.
 * T must be a subclass of ZSymbol.
 */
	template<typename T, typename... Args>
	static sp<T> initScopeSymbol(sbx prnSc, Args&&... args) {
		static_assert(std::is_base_of_v<ZSymbol, T>,
						  "initScopeSymbol: T must be derived from ZSymbol");
		zaccert(prnSc->getZSymbol() == nullptr,
				  "Parent symbol in scope should be null before initializing");
		sp<T> sym = ms<T>(std::forward<Args>(args)...);
		prnSc->setZSymbol(sym);
		return sym;
	}
}

