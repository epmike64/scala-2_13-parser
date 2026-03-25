#pragma once
#include <vector>

#include "fTraitDef.hpp"
#include "util/fCommon.hpp"
#include "ast/node/fAstOprndNod.hpp"

namespace zebra::ast::leaf {
	class fAccessModifier;
	class fClassParamClauses;
	using namespace zebra::ast::node;
	using zebra::lex::token::fToken;
	using namespace zebra::util;

	class fClassDef : public fTraitDef {
		const bool isCaseClass_;
		sp<fClassParamClauses> classParamClauses_;
		sp<fAccessModifier> constrAccessModifier_;

	public:
		fClassDef(const fToken *className, sp<fModifiers> &&modifiers, bool isCaseClass) ;

		void setConstrAccessModifier(sp<fAccessModifier> &&constrAccessModifier);

		sp<fAccessModifier> getConstrAccessModifier();

		void setClassParamClauses(sp<fClassParamClauses> &&classParamClauses);

		sp<fClassParamClauses> getClassParamClauses() const {
			return classParamClauses_;
		}

		bool isCaseClass() const {
			return isCaseClass_;
		}


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return CLASS_DEF;
		}
	};
}
