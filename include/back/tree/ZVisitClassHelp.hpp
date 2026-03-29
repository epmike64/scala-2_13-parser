#pragma once
#include "ast/leaf/fClassDef.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace util;
	using namespace ast::node;
	class ZVisitClassHelp {
		public:
		static void visitClassDef(sp<fClassDef> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitObjectDef(sp<fObjectDef> n, ssc prnSc, sp<fAstNodVisitor> visitor) ;
		static void visitClassTemplate(sp<fClassTemplate> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTemplate(sp<fTemplate> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitBlock(sp<fBlock> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTemplateBody(sp<fTemplateBody> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitTraitDef(sp<fTraitDef> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitClassParents(sp<fClassParents> n, ssc prnSc, sp<fAstNodVisitor> visitor);
		static void visitClassConstr(sp<fClassConstr> n, ssc prnSc, sp<fAstNodVisitor> visitor);
	};
}
