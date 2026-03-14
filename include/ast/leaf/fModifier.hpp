#pragma once

#include "../symbol/ZEnclosingScope.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "lex/kind/fLangModifierTypeE.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace zebra::ast::symbol;

	class fModifier : public fAstOprndNod {
		const lex::kind::fLangModifierTypeE _modType;
	protected:
		fModifier(lex::kind::fLangModifierTypeE modType) : _modType(modType) {}

	public:

		lex::kind::fLangModifierTypeE getModifierType() const { return _modType; }

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}