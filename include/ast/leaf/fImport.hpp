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

		std::string toString() const ;
	};

	class fImportExpr {
		const sp<fStableId> sid_;
		sp<std::vector<sp<fImportSelector>>> selectors_;
		const fToken* underscore_;
	public:
		fImportExpr(sp<fStableId> &&sid) ;

		void setUnderscore(const fToken *underscore);

		const fToken *getUnderscore() const;

		void setSelectors(sp<std::vector<sp<fImportSelector>>> &&selectors) ;

		sp<fStableId> getId() const ;

		sp<std::vector<sp<fImportSelector>>> getSelectors() ;

		std::string toString() const ;
	};

	class fImport : public fLangOprnd{
		std::vector<sp<fImportExpr>> importExprs_;
		public:
		fImport() = default;

		void addImportExpr(sp<fImportExpr> &&expr);

		std::vector<sp<fImportExpr>> getImportExprs();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return IMPORT;
		 }
	};
}