#include "ast/leaf/fTemplate.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	fTemplate::fTemplate(sp<fTemplateBody> &&body, bool amExtender) : templateBody_(std::move(body)), amExtender_(amExtender) {
	}

	void fTemplate::accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) {
		visitor->visit(std::static_pointer_cast<fTemplate>(shared_from_this()), s);
	}

	std::string fTemplate::toString() const {
		return "AccessModifier()";
	}
}