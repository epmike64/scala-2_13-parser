#pragma once

#include "fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTemplate : public fLangOprnd {
		const sp<fTemplateBody> templateBody_;
		const bool amExtender_;
		public:

		fTemplate(sp<fTemplateBody> &&body, bool amExtender);

		sp<fTemplateBody> getTemplateBody() const {
			return templateBody_;
		}

		bool amExtender() const {
			return amExtender_;
		}


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return TEMPLATE;
		}
	};
}