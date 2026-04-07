
#include "back/code/XVisitor.hpp"

#include <iostream>

#include "util/fUtil.hpp"

namespace zebra::back::code {

	XVisitor::XVisitor(sp<ZProgram> program) : zProgram_(std::move(program)) {
		zaccert(zProgram_ != nullptr, "ZProgram cannot be null for code generation");
	}

	void XVisitor::visit(sp<ZCompileUnit> zCompileUnit) {
		std::cout << "Visiting compile unit: " << zCompileUnit->toString() << std::endl;
		for (const auto& stmt : *zCompileUnit->getStmts()) {
			visit(stmt);
		}
	}
	void XVisitor::visit(sp<ZClassDef> zClassDef) {
		std::cout << "Visiting class definition: " << std::endl;
		// Here you would add the actual code generation logic for the class definition
	}

	void XVisitor::visit(sp<ZObjectDef> zObjectDef) {
		std::cout << "Visiting object definition: "  << std::endl;
		// Here you would add the actual code generation logic for the object definition
	}

	void XVisitor::visit(sp<ZSymbol> zSymbol) {
		std::cout << "Visiting symbol: " << std::endl;
	}
}
