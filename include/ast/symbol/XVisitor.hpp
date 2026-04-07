#pragma once
#include "util/fCommon.hpp"
#include "XEnclSc.hpp"

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
		void visit(sp<ZCompileUnit>, EncSc);
		void visit(sp<ZClassDef>, EncSc);
		void visit(sp<ZObjectDef>, EncSc);
		void visit(sp<ZTraitDef> , EncSc);
		void visit(sp<ZSymbol>,  EncSc);
	};
}
