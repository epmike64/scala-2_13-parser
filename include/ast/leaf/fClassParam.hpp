#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVariableMutabilityTypeE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassParam : public fAstOprndNod {
		const fToken *identifier_;
		lex::kind::fVariableMutabilityTypeE mutability_ = lex::kind::fVariableMutabilityTypeE::NONE;
		sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> defaultValueExpr_;
		sp<fModifiers> modifiers_;

	public:
		fClassParam() = default;

		void setIdentifier(const fToken* identifier);

		void setMutability(lex::kind::fVariableMutabilityTypeE mutability) ;

		void setParamType(sp<fParamType> &&paramType) ;

		void setDefaultValueExpr(sp<fAstProdSubTreeN> &&defaultValue);

		void setModifiers(sp<fModifiers> &&modifiers) ;

		const fToken* getIdentifier() const;

		lex::kind::fVariableMutabilityTypeE getMutability() const;
		sp<fParamType> getParamType() const;
		sp<fAstProdSubTreeN> getDefaultValueExpr() const;
		sp<fModifiers> getModifiers() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;

		std::string toString() const override;
	};
}
