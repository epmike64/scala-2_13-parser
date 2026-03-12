
#pragma once
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::tree {

	using namespace ast::node;

	class fLangAstTree {
	public:
		fLangAstTree() = default;
		~fLangAstTree() = default;
		virtual std::string toString() const = 0;
	};

	class fBinary: public fLangAstTree {
		sp<fAstOprndNod> left_;
		sp<fAstOprndNod> right_;
		sp<node::fAstOptrNod> optr_;
	public:

		void setLeft(sp<fAstOprndNod> left);

		void setRight(sp<fAstOprndNod> right) ;
		void setOptr(sp<fAstOptrNod> optr) ;

		sp<fAstOptrNod> getOperator() const;

		sp<fAstOprndNod> getLeft() const;

		sp<fAstOprndNod> getRight() const ;

		std::string toString() const override;
	};

}
