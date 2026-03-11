

#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "cassert"

namespace zebra::ast::node {

	void fAstNod::setAstParentN(std::shared_ptr<fAstNod> p) {
		assert(p->isOperator());
		this->astParentN_ = p;
	}

}

