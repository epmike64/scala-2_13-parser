#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fPackage : public fLangOprnd {
		const std::vector<const fToken*> ids_;
		public:
			fPackage(std::vector<const fToken*> &&ids) ;

		std::vector<const fToken*> getIds() const;
		std::string getPackgQualName() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::PACKAGE;
		 }
	};
}