#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using std::vector;

	class fClassParamClauses : public fAstOprndNod {
		vector<sp<fClassParam>> implicitParams_;
		vector<vector<sp<fClassParam>>> classParams_;
		public:

		fClassParamClauses() = default;

		void setImplicitParams(vector<sp<fClassParam>> &&implicitParams) ;

		void addParams(vector<sp<fClassParam>> &&params);

		 vector<sp<fClassParam>> getImplicitParams() const ;
		 vector<vector<sp<fClassParam>>> getClassParams() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;
		std::string toString() const override;
	};
}