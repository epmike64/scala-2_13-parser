#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitModHelp {
		public:
		static void visitOverrideMod(sp<fOverrideModifier> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitAccessMod(sp<fAccessModifier> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitLocalMod(sp<fLocalModifier> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitModifiers(sp<fModifiers> n, ssc, sp<fAstNodVisitor> visitor);
	};
}