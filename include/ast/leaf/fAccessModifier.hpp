#pragma once

#include "fModifier.hpp"
#include "ast/node/EnclsScope.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fAccessModifier : public fModifier {
		sp<fAccessQualifier> qualifier_;
	public:
		fAccessModifier(lex::kind::fLangModifierTypeE modType) : fModifier(modType) {}

		 void setQualifier(sp<fAccessQualifier> &&qualifier) ;

		 sp<fAccessQualifier> getQualifier() const {
			return qualifier_;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}