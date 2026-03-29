#pragma once

#include <vector>

#include "fType.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fTypeArgs : public fLangOprnd {
		const std::vector<sp<fType>> typeArgs_;
		public:

		fTypeArgs(std::vector<sp<fType>> &&typeArgs);

		 const std::vector<sp<fType>>& getTypeArgs() const ;
		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::TYPE_ARGS;
		 }
	};
}