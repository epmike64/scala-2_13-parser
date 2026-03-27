#pragma once

#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include <vector>
#include <stdexcept>

#include "../fLangOperand.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::util;

	class fCompileUnit : public fLangOprnd {
		std::vector<sp<fPackage>> _packages;
		std::vector<sp<fAstNod>> _stmts;
	public:
		fCompileUnit() = default;

		void addStmt(sp<fAstNod>&& stmt) ;
		std::vector<sp<fAstNod>>& getStmts();

		void addPackage(sp<fPackage>&& pkg);
		std::vector<sp<fPackage>>& getPackages() ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::COMPILE_UNIT;
		}
	};
}
