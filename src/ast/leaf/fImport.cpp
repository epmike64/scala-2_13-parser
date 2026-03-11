#include "ast/leaf/fImport.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fImportExpr::fImportExpr(sp<fStableId> &&id) : id(std::move(id)) {}

	void  fImportExpr::setSelectors(std::vector<sp<fImportSelector>> &&selectors) {
		this->selectors = std::move(selectors);
	}

	sp<fStableId> fImportExpr::getId() const {
		return id;
	}

	std::vector<sp<fImportSelector>> fImportExpr::getSelectors() {
		return selectors;
	}

	void fImport::addImportExpr(sp<fImportExpr> &&expr) {
		importExprs_.push_back(std::move(expr));
	}

	std::vector<sp<fImportExpr>> fImport::getImportExprs()  {
		return importExprs_;
	}


	void fImport::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fImport>(shared_from_this()));
	}

	std::string fImport::toString() const {
		return "AccessModifier()";
	}
}