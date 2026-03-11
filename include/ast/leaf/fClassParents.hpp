#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassParents: public fAstOprndNod {
		sp<fClassConstr> constr_;
		std::vector<sp<fParamType>> withTypes_;
	public:

		fClassParents() = default;

		 void setConstr(sp<fClassConstr> &&constr) ;

		 void addWithType(sp<fParamType> &&withType);

		 sp<fClassConstr> getConstr() const;

		 std::vector<sp<fParamType>> getWithTypes() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}