#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "lex/kind/fLangModifierTypeE.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fModifiers : public fLangOprnd {
		sp<fAccessModifier> accessModifier_;
		sp<fOverrideModifier> overrideModifier_;
		sp<std::vector<sp<fLocalModifier>>> localModifiers_;
	public:
		fModifiers() = default;

		void setAccessModifier(sp<fAccessModifier> &&accessModifier);

		void setOverrideModifier(sp<fOverrideModifier> &&overrideModifier);

		void addLocalModifier(sp<fLocalModifier> &&localModifier);

		sp<fAccessModifier> getAccessModifier() const;

		sp<fOverrideModifier> getOverrideModifier() const;

		sp<std::vector<sp<fLocalModifier>>> getLocalModifiers() const;


		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::MODIFIERS;
		 }
	};
}