#pragma once

#include "../fLangOperand.hpp"
#include "fParamType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fParam : public fLangOprnd {
		const fToken* identifier_;
		sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> defaultValue_;
		public:

		fParam(const fToken* identifier);

		void setParamType(sp<fParamType> &&paramType);

		void setDefaultValueExpr(sp<fAstProdSubTreeN> &&defaultValue);

		const fToken* getIdentToken() const;
		const std::string getIdentName() const;

		sp<fParamType> getParamType() const;

		sp<fAstProdSubTreeN> getDefaultValueExpr() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::PARAM;
		 }
	};
}