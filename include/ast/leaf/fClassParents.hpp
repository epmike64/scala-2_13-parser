#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassParents: public fLangOprnd {
		const sp<fClassConstr> constr_;
		sp<fParamType> withTypes_;
	public:

		fClassParents(sp<fClassConstr> &&constr);

		 void setWithType(sp<fParamType> &&withType);

		 sp<fClassConstr> getConstr() const;

		 sp<fParamType> getWithTypes() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::CLASS_PARENTS;
		}
	};
}