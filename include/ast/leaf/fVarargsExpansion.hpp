#pragma once
#include "ast/fLangOperand.hpp"
#include "ast/node/fAstOptrNod.hpp"
#include "lex/token/fToken.hpp"


namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fVarargsExpansion : public fLangOprnd {
		const fToken* varargsFirstToken_;
	public:
		fVarargsExpansion(const fToken* varargsFirstToken);

		const fToken* getIdentToken() const ;

		std::string getIdentName() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::VARARGS_EXPANSION;
		}
	};
}
