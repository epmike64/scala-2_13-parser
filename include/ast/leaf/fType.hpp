#pragma once
#include "ast/node/EnclsScope.hpp"
#include "lex/token/fToken.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::lex::token;

	class fType : public fAstOprndNod {
		const sp<fAstProdSubTreeN> _typeTree;
	public:
		fType(sp<fAstProdSubTreeN> &&typeTree);

		const sp<fAstProdSubTreeN> &getType() const;

		 void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;

		std::string toString() const override;

	};

}
