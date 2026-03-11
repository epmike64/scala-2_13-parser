#pragma once

#include "fTemplate.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassTemplate : public fTemplate {
		const sp<fClassParents> parents_;
		public:

		fClassTemplate(sp<fTemplateBody> &&body, bool amExtender, sp<fClassParents> &&parents) ;


		sp<fClassParents> getClassParents() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}