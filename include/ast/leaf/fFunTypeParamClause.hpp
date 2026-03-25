#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "fTypeParam.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFunTypeParamClause : public fLangOprnd{
		std::vector<sp<fTypeParam>> typeParams_;
	public:
		fFunTypeParamClause(std::vector<sp<fTypeParam>> typeParam) ;
		const std::vector<sp<fTypeParam>>& getTypeParamList();
		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
		fLangOprndType getLangOprndType() override {
			return FUN_TYPE_PARAM_CLAUSE;
		 }
	};
}