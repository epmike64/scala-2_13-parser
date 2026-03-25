#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fParamTypes : public fLangOprnd {
		const sp<std::vector<sp<fParamType>>> paramTypes_;
		public:

		fParamTypes(sp<std::vector<sp<fParamType>>> &&paramTypes);
		 sp<std::vector<sp<fParamType>>> getParamTypes() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return PARAM_TYPES;
		 }
	};
}