#pragma once

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fParam : public fAstOprndNod {
		const fToken* identifier_;
		sp<fParamType> paramType_;
		sp<fAstProdSubTreeN> defaultValue_;
		public:

		fParam(const fToken* identifier);

		void setParamType(sp<fParamType> &&paramType);

		void setDefaultValue(sp<fAstProdSubTreeN> &&defaultValue);

		const fToken* getIdentifier() const;

		sp<fParamType> getParamType() const;

		sp<fAstProdSubTreeN> getDefaultValue() const;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}