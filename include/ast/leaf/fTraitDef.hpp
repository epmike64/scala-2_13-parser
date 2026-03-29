#pragma once

#include <vector>

#include "fClassParamClauses.hpp"
#include "../fLangOperand.hpp"
#include "fTypeParamClause.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTraitDef : public fLangOprnd {
	protected:
		const fToken* identName_;
		const sp<fModifiers> modifiers_;
		sp<fTypeParamClause> typeParamClause_;
		sp<fTemplate> extendsTemplate_;
		public:

		fTraitDef(const fToken* traitName, sp<fModifiers> &&modifiers);

		 const fToken* getIdentToken() const ;

		const std::string& getIdentName() const;

		 sp<fModifiers> getModifiers() const;

		 void setTypeParamClause(const sp<fTypeParamClause> &typeParams);

		sp<fTypeParamClause> getTypeParamClause() const;

		 void setExtendsTemplate(sp<fTemplate> &&extendsTemplate);

		 sp<fTemplate> getExtendsTemplate() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TRAIT_DEF;
		}
	};
}