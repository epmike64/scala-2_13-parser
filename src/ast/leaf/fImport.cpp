#include "ast/leaf/fImport.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fStableId.hpp"

namespace zebra::ast::leaf {
	fImportExpr::fImportExpr(sp<fStableId> &&sid) : sid_(std::move(sid)) {
	}

	void fImportExpr::setSelectors(std::vector<sp<fImportSelector> > &&selectors) {
		this->selectors_ = std::move(selectors);
	}

	sp<fStableId> fImportExpr::getId() const {
		return sid_;
	}

	std::vector<sp<fImportSelector> > fImportExpr::getSelectors() {
		return selectors_;
	}

	void fImport::addImportExpr(sp<fImportExpr> &&expr) {
		importExprs_.push_back(std::move(expr));
	}

	std::vector<sp<fImportExpr> > fImport::getImportExprs() {
		return importExprs_;
	}

	std::string fImportSelector::toString() const {
		return "ImportSelector(from: " + from->toString() + ", to: " + to->toString() + ")";
	}

	std::string fImportExpr::toString() const {
		std::stringstream ss;
		ss << "ImportExpr(" << sid_->toString();
		if (!selectors_.empty()) {
			ss << " with selectors: [";
			for (std::size_t i = 0; i < selectors_.size(); i++) {
				ss << selectors_[i]->toString();
				if (i < selectors_.size() - 1) {
					ss << ", ";
				}
			}
			ss << "]";
		}
		ss << ")";
		return ss.str();
	}


	void fImport::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fImport>(shared_from_this()));
	}

	std::string fImport::toString() const {
		std::stringstream ss;
		for (std::size_t i; i < importExprs_.size(); i++) {
			ss << importExprs_[i]->toString();
			if (i < importExprs_.size() - 1) {
				ss << ", ";
			}
		}
		return "Import(" + ss.str() + ")";
	}
}
