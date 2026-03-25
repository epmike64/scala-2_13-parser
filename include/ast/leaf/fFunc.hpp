#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFunc : public fLangOprnd {
		const sp<fModifiers> modifiers_;
	protected:
		fFunc(sp<fModifiers> &&modifiers);
	public:
		~fFunc() = default;
		 sp<fModifiers> getModifiers() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::FUNC;
		 }
	};
}