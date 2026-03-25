#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "lex/kind/fVarMutTypeE.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fClassParam : public fLangOprnd {
		const fToken *identifier_;
		lex::kind::fVarMutTypeE mutability_ = lex::kind::fVarMutTypeE::NONE;
		sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> defaultValueExpr_;
		sp<fModifiers> modifiers_;

	public:
		fClassParam() = default;

		void setIdentifier(const fToken* identifier);

		void setMutability(lex::kind::fVarMutTypeE mutability) ;

		bool isMutable();

		void setParamType(sp<fParamType> &&paramType) ;

		void setDefaultValueExpr(sp<fAstProdSubTreeN> &&defaultValue);

		void setModifiers(sp<fModifiers> &&modifiers) ;

		const fToken* getIdentToken() const;

		const std::string getIdentName() const;

		lex::kind::fVarMutTypeE getMutability() const;
		sp<fParamType> getParamType() const;
		sp<fAstProdSubTreeN> getDefaultValueExpr() const;
		sp<fModifiers> getModifiers() const;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return CLASS_PARAM;
		}
	};
}
