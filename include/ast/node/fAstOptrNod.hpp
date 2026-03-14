#pragma once
#include <memory>
#include "ast/node/fAstNod.hpp"

#include "lex/kind/fLangOperatorKind.hpp"
#include "lex/token/fToken.hpp"

namespace zebra::ast::node { class fAstNodVisitor; }

namespace zebra::ast::node {

	using lex::kind::fLangOperatorKind;
	using lex::token::fToken;

	class fAstOptrNod : public fAstNod{
	private:
		const fLangOperatorKind* operatorKind_;
		const fToken* operatorToken_;
	public:
		fAstOptrNod(const fLangOperatorKind *kind, const fToken* token);

		const fLangOperatorKind *getLangOptrKnd();

		bool isOperator() override;

		fAstNodKndE astNKndE() override;

		void setAstLeftN(std::shared_ptr<fAstNod> astLeftN) override;

		void setAstRightN(std::shared_ptr<fAstNod> astRightN) override;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, symbol::esc s) override;

		 std::string toString() const override;
	};
}
