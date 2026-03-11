#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTemplate : public fAstOprndNod {
		const sp<fTemplateBody> body_;
		const bool amExtender_;
		public:

		fTemplate(sp<fTemplateBody> &&body, bool amExtender);

		sp<fTemplateBody> getTemplateBody() const {
			return body_;
		}

		bool amExtender() const {
			return amExtender_;
		}


		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}