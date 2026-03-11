#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fParamTypes : public fAstOprndNod {
		const sp<std::vector<sp<fParamType>>> paramTypes_;
		public:

		fParamTypes(sp<std::vector<sp<fParamType>>> &&paramTypes);
		 sp<std::vector<sp<fParamType>>> getParamTypes() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}