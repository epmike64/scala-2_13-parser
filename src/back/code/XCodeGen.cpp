#include "back/code/XCodeGen.hpp"

#include <iostream>

namespace zebra::back::code {
	XCodeGen::XCodeGen(ast::node::sp<ast::symbol::ZProgram> zProgram) : zProgram_(std::move(zProgram)) {
		util::zaccert(zProgram_ != nullptr, "ZProgram cannot be null for code generation");
	}

	void XCodeGen::gen() {
		std::cout << "Generating code for program: " << zProgram_->toString() << std::endl;
		for (const auto& compileUnit : zProgram_->getCompileUnits()) {
			std::cout << "Generating code for compile unit: " << compileUnit->toString() << std::endl;
			// Here you would add the actual code generation logic for each compile unit
		}
	}
}
