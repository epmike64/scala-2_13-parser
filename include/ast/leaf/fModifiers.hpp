#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "lex/kind/fLangModifierTypeE.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fModifiers : public fAstOprndNod {
		sp<fAccessModifier> accessModifier_;
		sp<fOverrideModifier> overrideModifier_;
		sp<fLocalModifier> localModifier_;
	public:
		fModifiers() = default;

		void setAccessModifier(sp<fAccessModifier> &&accessModifier);

		void setOverrideModifier(sp<fOverrideModifier> &&overrideModifier);

		void setLocalModifier(sp<fLocalModifier> &&localModifier);

		sp<fAccessModifier> getAccessModifier() const;

		sp<fOverrideModifier> getOverrideModifier() const;

		sp<fLocalModifier> getLocalModifier() const;


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}