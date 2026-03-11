#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fImportSelector {
		const fToken *from, *to;
	public:
		fImportSelector(const fToken *from, const fToken *to) : from(from), to(to) {}

		const fToken *getFrom() const {
			return from;
		}

		const fToken *getTo()  const {
			return to;
		}
	};

	class fImportExpr {
		const sp<fStableId> id;
		std::vector<sp<fImportSelector>> selectors;
	public:
		fImportExpr(sp<fStableId> &&id) ;

		void setSelectors(std::vector<sp<fImportSelector>> &&selectors) ;

		sp<fStableId> getId() const ;

		std::vector<sp<fImportSelector>> getSelectors() ;
	};

	class fImport : public fAstOprndNod {
		std::vector<sp<fImportExpr>> importExprs_;
		public:
		fImport() = default;

		void addImportExpr(sp<fImportExpr> &&expr);

		std::vector<sp<fImportExpr>> getImportExprs();

		void accept(std::shared_ptr<fAstNodVisitor> visitor) override;
		std::string toString() const override;
	};
}