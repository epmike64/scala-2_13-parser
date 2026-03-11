#pragma once

#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstNodKndE.hpp"
#include "ast/node/fAstRootOptrNod.hpp"
#include "util/fCommon.hpp"

namespace zebra::parse {

	using namespace ast::node;
	using namespace zebra::util;
	
	class fAst {
		sp<fAstRootOptrNod> rootOp_ = std::make_shared<fAstRootOptrNod>();
		sp<fAstNod> astLast_ = std::dynamic_pointer_cast<fAstNod>(rootOp_);
		bool isCont_ = true;

	public:

		void setRight(sp<fAstNod> v);

		void setAstLastN(sp<fAstNod> v);

		sp<fAstNod> astLastN();

		sp<fAstRootOptrNod> astRootOpr();

		fAstNodKndE astLastNKnd();

		bool isContinue();

		void setIsContinue(bool isContinue);
	};

}
