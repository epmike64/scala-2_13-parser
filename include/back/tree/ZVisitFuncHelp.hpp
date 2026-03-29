#pragma once

#include <type_traits>

#include "ast/fLangOperand.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitFuncHelp {
	public:
		static void visitRegFunc(sp<fRegFunc> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitFunSig(sp<fFunSig> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitThisFunc(sp<fThisFunc> n, esc prnSc, sp<fAstNodVisitor> visitor);

		/**
		 * Creates a child ZEnclScope under prnSc, calls accept() on the node,
		 * and returns the new scope so the caller can retrieve the produced ZSymbol.
		 * T must be a subclass of fLangOprnd.
		 */
		template<typename T>
		static esc visitChildNode(sp<T> node, esc prnSc, sp<fAstNodVisitor> visitor) {
			static_assert(std::is_base_of_v<ast::fLangOprnd, T>,
			              "visitChildNode: T must be derived from fLangOprnd");
			esc subSc = ms<ZEnclScope>(prnSc);
			node->accept(visitor, subSc);
			return subSc;
		}

		/**
		 * Asserts the scope has no symbol yet, creates a ZSymbol subclass (forwarding
		 * any constructor arguments), registers it on prnSc, and returns it.
		 * T must be a subclass of ZSymbol.
		 */
		template<typename T, typename... Args>
		static sp<T> initScopeSymbol(esc prnSc, Args&&... args) {
			static_assert(std::is_base_of_v<ZSymbol, T>,
			              "initScopeSymbol: T must be derived from ZSymbol");
			zaccert(prnSc->getZSymbol() == nullptr,
			        "Parent symbol in scope should be null before initializing");
			sp<T> sym = ms<T>(std::forward<Args>(args)...);
			prnSc->setZSymbol(sym);
			return sym;
		}
	};
}