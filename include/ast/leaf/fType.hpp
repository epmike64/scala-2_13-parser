#pragma once

#include "../fLangOperand.hpp"
#include "lex/token/fToken.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::ast::symbol;
	using namespace zebra::lex::token;

	class fType : public fLangOprnd {
		const sp<fAstProdSubTreeN> typeTree_;
	public:
		fType(sp<fAstProdSubTreeN> &&typeTree);

		const sp<fAstProdSubTreeN> &getTypeTree() const;

		 void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TYPE;
		 }

	};

}
