#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fAccessQualifierE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fAccessQualifier : public fLangOprnd {
		const lex::kind::fAccessQualifierE _qualifier;
		const fToken* _id;
	public:

		fAccessQualifier(lex::kind::fAccessQualifierE qualifier, const fToken* id) : _qualifier(qualifier), _id(id) {}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::ACCESS_QUALIFIER;
		}
	};
}