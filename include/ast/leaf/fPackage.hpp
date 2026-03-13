#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fPackage : public fAstOprndNod {
		const std::vector<const fToken*> ids_;
		public:
			fPackage(std::vector<const fToken*> &&ids) ;

			 std::vector<const fToken*> getIds() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}