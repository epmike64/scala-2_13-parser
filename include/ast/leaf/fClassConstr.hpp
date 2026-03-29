#pragma once

#include "../fLangOperand.hpp"
#include "fParamType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassConstr : public fLangOprnd {
		const sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> args_;
	public:
		fClassConstr(sp<fParamType> &&paramType);

		sp<fParamType> getParamType() const ;

		 void setArgsExpr(sp<fAstProdSubTreeN>&& args) ;

		sp<fAstProdSubTreeN> getArgs() const ;


		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::CLASS_CONSTR;
		}
	};
}