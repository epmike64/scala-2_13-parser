#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fFun : public fAstOprndNod {
		const sp<fModifiers> modifiers_;
	protected:
		fFun(sp<fModifiers> &&modifiers);
	public:
		~fFun() = default;
		 sp<fModifiers> getModifiers() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}