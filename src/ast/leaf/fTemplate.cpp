#include "ast/leaf/fTemplate.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTemplate::fTemplate(sp<fTemplateBody> &&body, bool amExtender) : templateBody_(std::move(body)), amExtender_(amExtender) {
		if (this->templateBody_ == nullptr) {
			throw std::invalid_argument("Template body cannot be null");
		}
	}

	void fTemplate::accept(std::shared_ptr<fAstNodVisitor> visitor) {
		visitor->visit(std::static_pointer_cast<fTemplate>(shared_from_this()));
	}

	std::string fTemplate::toString() const {
		return "AccessModifier()";
	}
}