#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fValue : public fAstOprndNod {
		const sp<fModifiers> modifiers_;
		std::vector<sp<fAstProdSubTreeN>> names_;
		sp<fType> type_;
		sp<fAstProdSubTreeN> assignExpr_;
		public:

		fValue(sp<fModifiers> &&modifiers) ;

		 sp<fModifiers> getModifiers() const ;

		 void addName(sp<fAstProdSubTreeN> &&name);

		 std::vector<sp<fAstProdSubTreeN>> getNames() const ;

		 void setType(sp<fType> &&type) ;

		 sp<fType> getType() const ;

		 void setAssignExpr(sp<fAstProdSubTreeN> &&assignExpr) ;

		 sp<fAstProdSubTreeN> getAssignExpr() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}