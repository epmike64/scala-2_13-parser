#pragma once
#include "ast/leaf/fClassDef.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;
	class ZVisitClassHelp {
		public:
		static void visitClassDef(sp<fClassDef> cls, esc prnSc, sp<fAstNodVisitor> visitor);
	};
}
