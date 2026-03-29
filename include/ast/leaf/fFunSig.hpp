#pragma once

#include <vector>

#include "fFunTypeParamClause.hpp"
#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFunSig : public fLangOprnd {
		const fToken *identName_;
		sp<fParamClauses> paramClauses_;
		sp<fFunTypeParamClause> funTypeParamClause_;

	public:
		fFunSig(const fToken *funName);

		void setParamClauses(sp<fParamClauses> &&paramClauses);

		void setFunTypeParamClause(std::vector<sp<fTypeParam> > &&typeParam);

		const fToken *getIdentToken() const;

		std::string getIdentName() const;

		sp<fParamClauses> getParamClauses() const;

		sp<fFunTypeParamClause> getFunTypeParamClause() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::FUNC_SIG;
		 }
	};
}
