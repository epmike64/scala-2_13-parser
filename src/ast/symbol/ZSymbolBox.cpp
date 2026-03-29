#include "ast/symbol/ZSymbolBox.hpp"

namespace zebra::ast::symbol {
	ZSymbolBox::ZSymbolBox(){}

	// ssc ZSymScope::getParentScope() const {
	// 	return parentScope_;
	// }

	sp<ZSymbol> ZSymbolBox::getZSymbol() {
		return zSymbol_;
	}

	void ZSymbolBox::setZSymbol(sp<ZSymbol> zSymbol) {
		this->zSymbol_ = zSymbol;
	}
}
