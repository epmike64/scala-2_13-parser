#pragma once

#include <vector>

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fIds : public fLangOprnd {
		const std::vector<sp<fId>> _ids;
		public:

		fIds(std::vector<sp<fId>> &&ids) : _ids(std::move(ids)) {
			if (this->_ids.empty()) {
				throw std::invalid_argument("Identifiers cannot be empty");
			}
		}

		const std::vector<sp<fId>>& getIds() const {
			return _ids;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return IDS;
		 }
	};
}