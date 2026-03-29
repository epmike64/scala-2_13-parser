#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fUnderscore : public fLangOprnd {
		const fToken* _underscoreToken;
		public:

		fUnderscore(const fToken* underscoreToken);
		 const fToken* getUnderscoreToken() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::UNDERSCORE;
		 }
	};
}