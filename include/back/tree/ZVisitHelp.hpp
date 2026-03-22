# pragma once
#include "ast/symbol/ZLangConstruct.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitHelp {
	public:
		static esc getWrapScope(esc prnSc, ZLangConstruct lc);
		static void treePostOrderPush(util::sp<fAstNod> n, esc prnSc);
	
	};
}
