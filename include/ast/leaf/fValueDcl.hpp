#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVarMutTypeE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fValueDcl : public fLangOprnd {
		const lex::kind::fVarMutTypeE mutabilityType_;
		const sp<fModifiers> modifiers_;
		std::vector<sp<fAstProdSubTreeN>> names_;
		sp<fType> type_;
		sp<fAstProdSubTreeN> assignExpr_;
		public:

		fValueDcl(sp<fModifiers> &&modifiers, lex::kind::fVarMutTypeE mutabilityType) ;

		 sp<fModifiers> getModifiers() const ;

		 void addName(sp<fAstProdSubTreeN> &&name);

		 std::vector<sp<fAstProdSubTreeN>> getNames() const ;

		 void setType(sp<fType> &&type) ;

		 sp<fType> getType() const ;

		 void setAssignExpr(sp<fAstProdSubTreeN> &&assignExpr) ;

		 sp<fAstProdSubTreeN> getAssignExpr() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::VALUE_DCL;
		 }
	};
}