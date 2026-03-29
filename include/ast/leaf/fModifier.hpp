#pragma once

#include "../fLangOperand.hpp"
#include "../symbol/ZSymScope.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "lex/kind/fLangModifierTypeE.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace zebra::ast::symbol;

	class fModifier : public fLangOprnd {
		const fLangModifierTypeE _modType;
	protected:
		fModifier(fLangModifierTypeE modType) : _modType(modType) {}

	public:

		fLangModifierTypeE getModifierType() const { return _modType; }

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::MODIFIER;
		}

	};
}