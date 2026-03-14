#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "lex/kind/fLangModifierTypeE.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fModifiers : public fAstOprndNod {
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


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}