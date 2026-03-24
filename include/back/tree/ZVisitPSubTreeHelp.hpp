# pragma once
#include <stack>
#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "ast/symbol/ZSymbol.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class fAstStackItem {
		sp<fAstNod> node;
		bool leftVisited, rightVisited;
	public:
		fAstStackItem(sp<fAstNod> node) : node(node), leftVisited(false), rightVisited(false) {
			if (this->node == nullptr) {
				throw std::invalid_argument("AST node in stack item cannot be null");
			}
		}
		void setLeftVisited() { leftVisited = true; }
		void setRightVisited() { rightVisited = true; }
		bool isLeftVisited() const { return leftVisited; }
		bool isRightVisited() const { return rightVisited; }
		sp<fAstNod> getNode() const { return node; }
	};

	class ZVisitPSubTreeHelp {
	public:
		static esc getWrapScope(esc prnSc, ZLangConstruct lc);
		static void treePostOrderPush(sp<fAstNod> n, esc prnSc);
		static sp<fAstNod> getAstPSTreeRightN(sp<fAstProdSubTreeN> subTr);
		static void traverseProdSubTree(sp<fAstProdSubTreeN> subTr, esc prnSc, sp<fAstNodVisitor> visitor);
		static sp<ZProdSubTreeN> visitIntoSubTree(sp<fAstNod> node, esc prnSc, sp<fAstNodVisitor> visitor);
	};
}
