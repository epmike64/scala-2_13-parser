#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"
#include "ast/leaf/fParam.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	using std::vector;

	class fParamClauses : public fAstOprndNod {
		vector<vector<sp<fParam>>> params_;
		sp<vector<sp<fParam>>> implicitParams_;
	public:

		fParamClauses() = default;

		void addParams(vector<sp<fParam>> &&params);

		 void setImplicitParams(std::vector<sp<fParam>> &&implicitParams);

		 vector<vector<sp<fParam>>> getParamLists() const ;

		sp<vector<sp<fParam>>> getImplicitParamList() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}