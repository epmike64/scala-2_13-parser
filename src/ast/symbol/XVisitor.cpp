
#include "../../../include/ast/symbol/XVisitor.hpp"
#include "ast/symbol/ZSymbol.hpp"

#include <iostream>

#include "util/fUtil.hpp"

namespace zebra::ast::symbol {

	XVisitor::XVisitor(sp<ZProgram> program) : zProgram_(std::move(program)) {
	}

	void XVisitor::visit() {
		EncSc sc = ms<XEnclSc>(nullptr);
		for (const auto& cu : zProgram_->getCompileUnits()) {
			visit(cu, sc);
		}
	}

	void XVisitor::visit(sp<ZCompileUnit> zCompileUnit, EncSc sc) {
		std::cout << "Visiting compile unit: " << zCompileUnit->toString() << std::endl;
		for (const auto& stmt : *zCompileUnit->getStmts()) {
			stmt->accept(shared_from_this(), sc);
		}
	}

	void XVisitor::visit(sp<ZClassDef> zClassDef, EncSc sc) {
		std::cout << "Visiting class definition: " << std::endl;
	}

	void XVisitor::visit(sp<ZObjectDef> zObjectDef, EncSc sc) {
		std::cout << "Visiting object definition: "  << std::endl;
	}

	void XVisitor::visit(sp<ZTraitDef> zTraitDef, EncSc sc) {
		std::cout << "Visiting trait definition: " << std::endl;
	}

	void XVisitor::visit(sp<ZSymbol> zSymbol, EncSc sc) {
		std::cout << "Visiting symbol: " << std::endl;
	}
}
