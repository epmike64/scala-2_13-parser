#pragma once


#include "ast/symbol/ZLangConstruct.hpp"
#include "ast/node/fAstNodVisitor.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;

	class ZVisitModHelp {
		public:
		static void visitOverrideMod(sp<fOverrideModifier> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitAccessMod(sp<fAccessModifier> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitLocalMod(sp<fLocalModifier> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitModifiers(sp<fModifiers> n, esc, sp<fAstNodVisitor> visitor);
	};
}