#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

		class fFunSig : public fAstOprndNod {
			const fToken* identName_;
			sp<fParamClauses> paramClauses_;
			sp<std::vector<sp<fTypeParam>>> typeParam_;
		public:
			fFunSig(const fToken* funName);
			 void setParamClauses(sp<fParamClauses> &&paramClauses) ;

			 void setTypeParams(std::vector<sp<fTypeParam>> &&typeParam);

			 const fToken* getIdentToken() const;
			 std::string getIdentName() const;

			 sp<fParamClauses> getParamClauses() const ;

			sp<std::vector<sp<fTypeParam>>> getTypeParamList() const;

			void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
			std::string toString() const override;
		};
}