#pragma once

#include "fType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fParamType : public fType {
	const bool isFatArrow, isStar;
		public:
		fParamType(sp<fType> &&type, bool isFatArrow, bool isStar) ;
		const bool getIsFatArrow() const {
			return isFatArrow;
		}

		const bool getIsStar() const {
			return isStar;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::PARAM_TYPE;
		 }
	};
}