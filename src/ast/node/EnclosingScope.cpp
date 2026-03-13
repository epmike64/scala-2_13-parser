#include "ast/node/EnclosingScope.hpp"

namespace zebra::ast::node {

	void EnclosingScope::setParentScope(esc parentScope) {
		parentScope_ = parentScope;
	}
	esc EnclosingScope::getParentScope() {
		return parentScope_;
	}

}