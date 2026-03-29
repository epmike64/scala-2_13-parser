#include "ast/leaf/fUnderscore.hpp"
#include "ast/node/fAstNodVisitor.hpp"

#include <string>

namespace zebra::ast::leaf {

	 fUnderscore::fUnderscore(const fToken* underscoreToken) : _underscoreToken(underscoreToken) {
		if (this->_underscoreToken == nullptr) {
			throw std::invalid_argument("Underscore token cannot be null");
		}
	}

	const fToken*  fUnderscore::getUnderscoreToken() const {
		return _underscoreToken;
	}

	void fUnderscore::accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) {
		visitor->visit(std::static_pointer_cast<fUnderscore>(shared_from_this()), s);
	}

	std::string fUnderscore::toString() const {
		return "Underscore(" + _underscoreToken->toString() + ")";
	}
}