#pragma once

#include <string>
#include <vector>

#include "ZEnclScopeFwd.hpp"
#include "../node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"
#include "ZSymbol.hpp"


namespace zebra::ast::symbol {

	using namespace zebra::ast::node;
	using namespace zebra::lex::kind;
	using namespace zebra::util;
	using symbol::ZSymbol;


	class ZSymbol;

	class ZSymScope {
	protected:
		sp<ZSymbol> zSymbol_;
	public:

		ZSymScope();
		sp<ZSymbol> getZSymbol();
		void setZSymbol(sp<ZSymbol> zSymbol) ;
	};
}
