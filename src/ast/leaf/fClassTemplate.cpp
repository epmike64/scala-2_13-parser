#include "ast/leaf/fClassTemplate.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fClassTemplate::fClassTemplate(sp<fTemplateBody> &&body, bool amExtender, sp<fClassParents> &&parents) : fTemplate(std::move(body), amExtender), parents_(std::move(parents)) {
		if (this->parents_ == nullptr) {
			throw std::invalid_argument("Class parents cannot be null");
		}
	}

	sp<fClassParents> fClassTemplate::getClassParents() const {
		return parents_;
	}


	void fClassTemplate::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fClassTemplate>(shared_from_this()));
	}

	std::string fClassTemplate::toString() const {
		return "AccessModifier()";
	}
}