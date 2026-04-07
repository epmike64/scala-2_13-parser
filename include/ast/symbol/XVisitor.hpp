#pragma once
#include "util/fCommon.hpp"

namespace zebra::ast::symbol {

	// forward declarations to avoid circular header dependency with ZSymbol.hpp
	class ZProgram;
	class ZCompileUnit;
	class ZClassDef;
	class ZObjectDef;
	class ZTraitDef;
	class ZSymbol;

	using namespace zebra::util;

	class XVisitor: public std::enable_shared_from_this<XVisitor> {
	protected:
		sp<ZProgram> zProgram_;
		public:
		explicit XVisitor(sp<ZProgram> program) ;
		virtual ~XVisitor() = default;
		void visit();
		void visit(sp<ZCompileUnit> zCompileUnit);
		void visit(sp<ZClassDef> zClassDef);
		void visit(sp<ZObjectDef> zObjectDef);
		void visit(sp<ZTraitDef> zTraitDef);
		void visit(sp<ZSymbol> zSymbol);
	};
}
