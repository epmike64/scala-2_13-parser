
#include "ast/symbol/XEnclSc.hpp"

namespace zebra::ast::symbol {

	XEnclSc::XEnclSc(sp<XEnclSc> parentScope) : parentScope_(parentScope) {}
	sp<XEnclSc> XEnclSc::getParentScope()  { return parentScope_; }

}

