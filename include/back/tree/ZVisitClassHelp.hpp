#pragma once
#include "ast/leaf/fClassDef.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;
	class ZVisitClassHelp {
		public:
		static void visitClassDef(sp<fClassDef> cls, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitObjectDef(sp<fObjectDef> obj, esc prnSc, sp<fAstNodVisitor> visitor) ;
		static void visitClassTemplate(sp<fClassTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTemplate(sp<fTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitBlock(sp<fBlock> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTemplateBody(sp<fTemplateBody> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTraitDef(sp<fTraitDef> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitClassParents(sp<fClassParents> n, esc prnSc, sp<fAstNodVisitor> visitor);
		static void visitClassConstr(sp<fClassConstr> n, esc prnSc, sp<fAstNodVisitor> visitor);
	};
}
