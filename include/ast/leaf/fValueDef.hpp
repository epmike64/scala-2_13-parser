#pragma once
#include <vector>

#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"
#include "fType.hpp"
#include "fValue.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace ast::symbol;

	class fValueDef : public fValue {
	public:
		fValueDef(sp<fModifiers>&& modifiers) ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

	};
}
