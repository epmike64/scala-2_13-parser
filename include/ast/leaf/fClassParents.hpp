#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassParents: public fAstOprndNod {
		sp<fClassConstr> constr_;
		sp<fParamType> withTypes_;
	public:

		fClassParents() = default;

		 void setConstr(sp<fClassConstr> &&constr) ;

		 void setWithType(sp<fParamType> &&withType);

		 sp<fClassConstr> getConstr() const;

		 sp<fParamType> getWithTypes() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}