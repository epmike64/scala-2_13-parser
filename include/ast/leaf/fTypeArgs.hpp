#pragma once

#include <vector>

#include "fType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTypeArgs : public fAstOprndNod {
		const std::vector<sp<fType>> typeArgs_;
		public:

		fTypeArgs(std::vector<sp<fType>> &&typeArgs);

		 const std::vector<sp<fType>>& getTypeArgs() const ;
		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}