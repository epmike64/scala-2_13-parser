#pragma once

#include "../fLangOperand.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fId : public fLangOprnd {
		const fToken* _id;
		public:

		fId(const fToken* id) : _id(id) {
			if (this->_id == nullptr) {
				throw std::invalid_argument("Identifier token cannot be null");
			}
		}

		 const fToken* getId() const {
			return _id;
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, ssc s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::ID;
		 }
	};
}