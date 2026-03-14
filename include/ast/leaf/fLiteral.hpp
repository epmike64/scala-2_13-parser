#pragma once
#include "lex/token/fToken.hpp"
#include "ast/node/fAstOprndNod.hpp"


namespace zebra::ast::leaf {

	using lex::kind::fTKnd;
	using namespace lex::token;
	using namespace zebra::ast::node;
	using namespace zebra::ast::symbol;


	class fLiteral: public fAstOprndNod {
		const fToken* _literalName;
		const fTKnd* _kind;
	public:
		fLiteral(const fToken* literalName, const fTKnd* knd) : _literalName(literalName), _kind(knd) {
		}

		const fToken* getLiteralName() const {
			return _literalName;
		}

		const fTKnd* getKind() const {
			return _kind;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

	};

}
