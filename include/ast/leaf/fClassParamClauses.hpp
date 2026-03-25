#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using std::vector;

	class fClassParamClauses : public fLangOprnd{
		vector<sp<fClassParam> > implicitParams_;
		vector<vector<sp<fClassParam> > > classParams_;

	public:
		fClassParamClauses() = default;

		void setImplicitParams(vector<sp<fClassParam> > &&implicitParams);

		void addParams(vector<sp<fClassParam> > &&params);

		vector<sp<fClassParam> > getImplicitClassParamList() const;

		vector<vector<sp<fClassParam> > > getClassParamLists() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::CLASS_PARAM_CLAUSES;
		}
	};
}
