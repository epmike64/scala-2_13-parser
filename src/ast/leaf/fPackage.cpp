#include "ast/leaf/fPackage.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fPackage::fPackage(std::vector<const fToken*> &&ids) : _ids(std::move(ids)) {
		if (this->_ids.empty()) {
			throw std::invalid_argument("Package identifiers cannot be empty");
		}
		for (const fToken* id : this->_ids) {
			if (id == nullptr) {
				throw std::invalid_argument("Package identifier cannot be null");
			}
		}
	}

	std::vector<const fToken*> fPackage::getIds() const {
		return _ids;
	}

	void fPackage::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fPackage>(shared_from_this()));
	}

	std::string fPackage::toString() const {
		std::stringstream ss;
		ss << "Package(";
		for (std::size_t i = 0; i < this->_ids.size(); i++) {
			ss << this->_ids[i]->toString();
			if (i < this->_ids.size() - 1) {
				ss << ".";
			}
		}
		ss << ")";
		return ss.str();
	}
}