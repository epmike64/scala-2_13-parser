#pragma once

#include "fParamType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassConstr : public fAstOprndNod {
		const sp<fParamType> paramType;
		sp<fAstProdSubTreeN> args_;
	public:
		fClassConstr(sp<fParamType> &&primaryCtorParamType);

		sp<fParamType> getPrimaryCtorParamType() const ;

		 void setArgsExpr(sp<fAstProdSubTreeN>&& args) ;

		sp<fAstProdSubTreeN> getArgs() const ;


		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}