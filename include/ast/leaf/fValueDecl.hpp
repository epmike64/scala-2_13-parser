#pragma once

#include "fValue.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fValueDecl : public fValue {
	public:

		fValueDecl(sp<fModifiers> &&modifiers) ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}