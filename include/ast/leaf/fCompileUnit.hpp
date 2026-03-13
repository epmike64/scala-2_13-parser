#pragma once

#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include <vector>
#include <stdexcept>

#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace zebra::ast::node;
	using namespace zebra::util;

	class fCompileUnit : public fAstOprndNod {
		std::vector<sp<fPackage>> _packages;
		std::vector<sp<fImport>> _imports;
		std::vector<sp<fAstNod>> _stmts;
	public:
		fCompileUnit() = default;

		void addStmt(sp<fAstNod>&& stmt) ;

		void addPackage(sp<fPackage>&& pkg);

		void addImport(sp<fImport>&& imp);

		std::vector<sp<fPackage>>& getPackages() ;
		std::vector<sp<fImport>>& getImports() ;
		 std::vector<sp<fAstNod>>& getStmts();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;

		std::string toString() const override;
	};
}
