#include "ast/leaf/fPackage.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fPackage::fPackage(std::vector<const fToken*> &&ids) : ids_(std::move(ids)) {
		if (this->ids_.empty()) {
			throw std::invalid_argument("Package identifiers cannot be empty");
		}
		for (const fToken* id : this->ids_) {
			if (id == nullptr) {
				throw std::invalid_argument("Package identifier cannot be null");
			}
		}
	}

	std::vector<const fToken*> fPackage::getIds() const {
		return ids_;
	}

	void fPackage::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fPackage>(shared_from_this()), s);
	}

	std::string fPackage::getPackageName() const {
		std::string packageName;
		for (size_t i = 0; i < ids_.size(); ++i) {
			packageName += ids_[i]->getTStrVal();
			if (i < ids_.size() - 1) {
				packageName += ".";
			}
		}
		return packageName;
	}


	std::string fPackage::toString() const {
		std::stringstream ss;
		ss << "Package(";
		for (std::size_t i = 0; i < this->ids_.size(); i++) {
			ss << this->ids_[i]->toString();
			if (i < this->ids_.size() - 1) {
				ss << ".";
			}
		}
		ss << ")";
		return ss.str();
	}
}