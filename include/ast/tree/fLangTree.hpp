
#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::tree {

	using namespace ast::node;

	class fLangTree {
	public:
		fLangTree() = default;
		~fLangTree() = default;
		virtual std::string toString() const = 0;
	};


	class fLangTrBranch: public fAstOprndNod {
	public:
		fLangTrBranch(const sp<fAstOprndNod> &left);

		void setRight(sp<fAstOprndNod> right) ;
		void setOptr(sp<fAstOptrNod> optr) ;

		sp<fAstOptrNod> getOperator() const;

		sp<fAstOprndNod> getLeft() const;

		sp<fAstOprndNod> getRight() const;

		std::string toString() const override;
	};
}
