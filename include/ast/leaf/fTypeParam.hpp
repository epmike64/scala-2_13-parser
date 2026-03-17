#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "lex/token/fToken.hpp"
#include "util/fCommon.hpp"

// fAstNodVisitor is forward-declared by fAstOprndNod.hpp.
// fTypeParamClause and fType are forward-declared in the namespace block below.

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;
	using namespace util;
	using zebra::lex::token::fToken;

	// Forward declarations — only sp<T> used, no full definition needed
	class fTypeParamClause;
	class fType;

	class fTypeParam : public fAstOprndNod {
	protected:
		const fToken* typeParamName_ = nullptr;
		sp<fTypeParamClause> typeParamClause_;
		sp<fType> upperBound_, lowerBound_;
		sp<std::vector<sp<fType>>> types_;
		sp<std::vector<sp<fType>>> contextBounds_;

	public:
		fTypeParam() = default;
		~fTypeParam() override = default;

		void setTypeParamName(const fToken* typeParamName);

		 const fToken* getTypeParamName() const ;

		void setTypeParamClause(const sp<fTypeParamClause> &typeParamClause);


		sp<fTypeParamClause> getTypeParamClause() const;

		 void addType(sp<fType> &&types) ;

		 sp<std::vector<sp<fType>>> getTypes() const;

		void addContextBound(sp<fType> &&contextBound) ;

		sp<std::vector<sp<fType>>> getContextBounds() const;

		 void setUpperBound(sp<fType> &&upperBound) ;

		 sp<fType> getUpperBound() const ;

		 void setLowerBound(sp<fType> &&lowerBound);

		 sp<fType> getLowerBound() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}