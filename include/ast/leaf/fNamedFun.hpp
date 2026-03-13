#pragma once

#include "fFun.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fNamedFun : public fFun {
		const sp<fFunSig> funSig_;
		sp<fType> returnType_;
		sp<fAstOprndNod> funBody_;
		public:

		fNamedFun(sp<fModifiers> &&modifiers, sp<fFunSig> &&funSig);

		 sp<fFunSig> getFunSig() const ;

		 sp<fType> getReturnType() const ;

		 sp<fAstOprndNod> getFunBody() const ;

		 void setReturnType(sp<fType> &&returnType);

		 void setFunBody(sp<fAstOprndNod> &&funBody) ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;
		std::string toString() const override;
	};
}