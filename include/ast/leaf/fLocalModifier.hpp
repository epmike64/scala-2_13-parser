#pragma once

#include "fModifier.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fLocalModifier : public fModifier {
	public:

		fLocalModifier(lex::kind::fLangModifierTypeE modType) : fModifier(modType) {}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;
		std::string toString() const override;
	};
}