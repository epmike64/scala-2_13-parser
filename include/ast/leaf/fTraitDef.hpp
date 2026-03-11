#pragma once

#include <vector>

#include "fClassParamClauses.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTraitDef : public fAstOprndNod {
		const fToken* traitName_;
		const sp<fModifiers> modifiers_;
		std::vector<sp<fVariantTypeParam>> typeParams_;
		sp<fTemplate> extendsTemplate_;
		public:

		fTraitDef(const fToken* traitName, sp<fModifiers> &&modifiers);

		 const fToken* getName() const ;

		 sp<fModifiers> getModifiers() const;

		 void setTypeParams(std::vector<sp<fVariantTypeParam>> &&typeParams);

		 std::vector<sp<fVariantTypeParam>> getTypeParams() const;

		 void setExtendsTemplate(sp<fTemplate> &&extendsTemplate);

		 sp<fTemplate> getExtendsTemplate() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}