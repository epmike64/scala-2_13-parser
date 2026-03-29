#pragma once


#include "../fLangOperand.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace ast::symbol;

	class fWhile  : public fLangOprnd {
		sp<fAstProdSubTreeN> condExpr;
		sp<fAstProdSubTreeN> body;
	public:
		fWhile(sp<fAstProdSubTreeN> &&condExpr) ;

		void setWhileBody(sp<fAstProdSubTreeN> &&body) ;

		sp<fAstProdSubTreeN> getCondExpr() const ;

		sp<fAstProdSubTreeN> getBody() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::WHILE;
		 }
	};
}