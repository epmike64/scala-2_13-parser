#include "parse/fAst.hpp"
#include "util/fCommon.hpp"


namespace zebra::parse {

		using namespace zebra::util;

		void fAst::setRight(sp<fAstNod> v) {
			assert(astLast_->isOperator() && "astRightN must be an operator");
			astLast_->setAstRightN(v);
			astLast_ = v;
		}

		void fAst::setAstLastN(sp<fAstNod> v) {
			astLast_ = v;
		}

		sp<fAstNod> fAst::astLastN()  {
			return astLast_;
		}

		fAstNodKndE fAst::astLastNKnd() {
			return astLast_->astNKndE();
		}

		bool fAst::isContinue() {
			return isCont_;
		}

		void fAst::setIsContinue(bool isContinue) {
			isCont_ = isContinue;
		}

		sp<fAstRootOptrNod> fAst::astRootOpr()  {
			return rootOp_;
		}
}