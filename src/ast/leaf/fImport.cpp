#include "ast/leaf/fImport.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fStableId.hpp"

namespace zebra::ast::leaf {
	fImportExpr::fImportExpr(sp<fStableId> &&sid) : sid_(std::move(sid)) {
	}

	void fImportExpr::setUnderscore(const fToken *underscore) {
		if (selectors_) {
			throw std::runtime_error("Cannot mark an import expression as underscore when it already has selectors");
		}
		this->underscore_ = underscore;
	}

	const fToken *fImportExpr::getUnderscore() const {
		return underscore_;
	}

	void fImportExpr::setSelectors(sp<std::vector<sp<fImportSelector>>> &&selectors) {
		if (this->getUnderscore() != nullptr) {
			throw std::runtime_error("Cannot set selectors for an import expression that is already marked as underscore");
		}
		this->selectors_ = std::move(selectors);
	}

	sp<fStableId> fImportExpr::getId() const {
		return sid_;
	}

	sp<std::vector<sp<fImportSelector>>> fImportExpr::getSelectors() {
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
		if (selectors_) {
			ss << " with selectors: [";
			for (std::size_t i = 0; i < selectors_->size(); i++) {
				ss << selectors_->at(i)->toString();
				if (i < selectors_->size() - 1) {
					ss << ", ";
				}
			}
			ss << "]";
		} else if (getUnderscore() != nullptr) {
			ss << " with underscore: " << getUnderscore()->toString();
		}
		ss << ")";

		return ss.str();
	}


	void fImport::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fImport>(shared_from_this()), s);
	}

	std::string fImport::toString() const {
		std::stringstream ss;
		for (std::size_t i = 0; i < importExprs_.size(); i++) {
			ss << importExprs_[i]->toString();
			if (i < importExprs_.size() - 1) {
				ss << ", ";
			}
		}
		return "Import(" + ss.str() + ")";
	}
}
