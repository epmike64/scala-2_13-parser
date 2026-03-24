#pragma once

#include "fParamType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassConstr : public fAstOprndNod {
		const sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> args_;
	public:
		fClassConstr(sp<fParamType> &&paramType);

		sp<fParamType> getParamType() const ;

		 void setArgsExpr(sp<fAstProdSubTreeN>&& args) ;

		sp<fAstProdSubTreeN> getArgs() const ;


		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}