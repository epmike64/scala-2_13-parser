#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fUnderscore : public fAstOprndNod {
		const fToken* _underscoreToken;
		public:

		fUnderscore(const fToken* underscoreToken);
		 const fToken* getUnderscoreToken() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}