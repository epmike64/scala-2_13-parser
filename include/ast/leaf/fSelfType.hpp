#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "fType.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fSelfType: public fLangOprnd {
		const fToken* selfToken_;
		sp<fType> selfType_;
	public:
		explicit fSelfType(const fToken* selfToken) ;

		void setSelfType(sp<fType> &&selfType);
		sp<fType> getSelfType();

		std::string toString() const override;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::SELF_TYPE;
		}
	};
}
