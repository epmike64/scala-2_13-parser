
#include "ast/leaf/fCompileUnit.hpp"

#include <string>

namespace zebra::ast::leaf {

	void fCompileUnit::addStmt(sp<fAstNod>&& stmt) {
		if (stmt == nullptr) {
			throw std::invalid_argument("Statement cannot be null");
		}
		_stmts.push_back(std::move(stmt));
	}

	void fCompileUnit::addPackage(sp<fPackage>&& pkg) {
		if (pkg == nullptr) {
			throw std::invalid_argument("Package cannot be null");
		}
		_packages.push_back(std::move(pkg));
	}

	void fCompileUnit::addImport(sp<fImport>&& imp) {
		if (imp == nullptr) {
			throw std::invalid_argument("Import cannot be null");
		}
		_imports.push_back(std::move(imp));
	}

	std::vector<sp<fPackage>>& fCompileUnit::getPackages() { return _packages; }
	std::vector<sp<fImport>>& fCompileUnit::getImports() { return _imports; }

	std::vector<sp<fAstNod>>& fCompileUnit::getStmts() {
		return _stmts;
	}

	void  fCompileUnit::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fCompileUnit>(shared_from_this()));
	}

	std::string fCompileUnit::toString() const {
		std::string result = "CompUnit(";
		for (size_t i = 0; i < _stmts.size(); ++i) {
			result += _stmts[i]->toString();
			if (i < _stmts.size() - 1) {
				result += ", ";
			}
		}
		result += ")";
		return result;
	}

}
