#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fCaseClause : public fAstOprndNod {
		sp<fAstProdSubTreeN> pattern;
		sp<fAstProdSubTreeN> guard;
		sp<fBlock> block;
		public:
		fCaseClause(sp<fAstProdSubTreeN> &&pattern) ;


		sp<fAstProdSubTreeN> getPattern() const ;

		sp<fAstProdSubTreeN> getGuard() const;

		sp<fBlock> getBlock() const ;

		void setGuard(sp<fAstProdSubTreeN> &&guard) ;
		void setBlock(sp<fBlock> &&block) ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}