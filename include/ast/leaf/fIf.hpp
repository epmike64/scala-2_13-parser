#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include <stdexcept>

#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fIf : public fAstOprndNod {
		sp<fAstProdSubTreeN> condExpr;
		sp<fAstProdSubTreeN> ifBody;
		sp<fAstProdSubTreeN> elseBody;

	public:
		fIf(sp<fAstProdSubTreeN> &&condExpr) : condExpr(std::move(condExpr)) {
			if (this->condExpr == nullptr) {
				throw std::invalid_argument("Condition expression cannot be null");
			}
		}

		void setIfBody(sp<fAstProdSubTreeN> &&ifBody) ;

		void setElseBody(sp<fAstProdSubTreeN> &&elseBody);

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		sp<fAstProdSubTreeN> getCondExpr() const {
			return condExpr;
		}

		sp<fAstProdSubTreeN> getIfBody() const {
			return ifBody;
		}

		sp<fAstProdSubTreeN> getElseBody() const {
			return elseBody;
		}

		std::string toString() const override;
	};
}
