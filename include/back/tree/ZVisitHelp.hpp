# pragma once
#include "ast/symbol/ZLangConstruct.hpp"

namespace zebra::back::tree {

	class ZVisitHelp {
		public:
		static ast::symbol::esc getWrapScope(ast::symbol::esc prnSc, ast::symbol::ZLangConstruct lc);
	};
}
