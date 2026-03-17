#pragma once

#include <vector>

#include "fClassParamClauses.hpp"
#include "fTypeParamClause.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTraitDef : public fAstOprndNod {
	protected:
		const fToken* traitName_;
		const sp<fModifiers> modifiers_;
		// sp<std::vector<sp<fVariantTypeParam>>> typeParams_;
		sp<fTypeParamClause> typeParams_;
		sp<fTemplate> extendsTemplate_;
		public:

		fTraitDef(const fToken* traitName, sp<fModifiers> &&modifiers);

		 const fToken* getName() const ;

		 sp<fModifiers> getModifiers() const;

		 void setVariantTypeParams(const sp<vector<sp<fVariantTypeParam>>> &typeParams);

		sp<fTypeParamClause> getVariantTypeParams() const;

		 void setExtendsTemplate(sp<fTemplate> &&extendsTemplate);

		 sp<fTemplate> getExtendsTemplate() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}