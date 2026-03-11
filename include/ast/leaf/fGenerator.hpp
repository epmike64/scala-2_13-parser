#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fGenerator : public fAstOprndNod {
		const sp<fAstProdSubTreeN> casePattern1_;
		const bool isCase;
		std::vector<sp<fAstProdSubTreeN>> guards_;
		sp<fAstProdSubTreeN> inExpr_;
		std::vector<sp<fAstProdSubTreeN>> endingPattern1s_;
		std::vector<sp<fAstProdSubTreeN>> endingExprs_;
		public:

		fGenerator(sp<fAstProdSubTreeN> &&casePattern1, bool isCase);

		void addGuard(sp<fAstProdSubTreeN> &&guard);

		 void setInExpr(sp<fAstProdSubTreeN> &&inExpr) ;

		 void addEndingPattern1(sp<fAstProdSubTreeN> &&endingPattern1);

		 void addEndingExpr(sp<fAstProdSubTreeN> &&endingExpr) ;
		 sp<fAstProdSubTreeN> getCasePattern1() const ;

		 bool isCaseGenerator() const ;

		 std::vector<sp<fAstProdSubTreeN>> getGuards() const;

		 sp<fAstProdSubTreeN> getInExpr() const;

		 std::vector<sp<fAstProdSubTreeN>> getEndingPattern1s() const ;

		 std::vector<sp<fAstProdSubTreeN>> getEndingExprs() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}