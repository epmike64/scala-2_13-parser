#include "ast/leaf/fIds.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

#include "ast/leaf/fId.hpp"

namespace zebra::ast::leaf {
	
	void fIds::accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) {
		visitor->visit(std::static_pointer_cast<fIds>(shared_from_this()), s);
	}

	std::string fIds::toString() const {
		return "Ids(ids=[" + [&]() {
			std::string result;
			for (const auto& id : _ids) {
				result += (id ? id->toString() : "null") + ", ";
			}
			return result;
		}() + "])";
	}
}
