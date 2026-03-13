
#pragma once

#include "ast/node/fAstNod.hpp"
#include "fAstNodKndE.hpp"

#include <memory>
#include <stdexcept>
#include <typeinfo>

#include "EnclsScope.hpp"

namespace zebra::ast::node { class fAstNodVisitor; }

namespace zebra::ast::node {

	class fAstOprndNod : public fAstNod {
	public:
		bool isOperator() override {
			return false;
		}

		fAstNodKndE astNKndE() override {
			return fAstNodKndE::AST_OPERAND;
		}

		void setAstLeftN(std::shared_ptr<fAstNod> astLeftN) override {
			throw std::runtime_error("Cannot set left operand for " + std::string(typeid(*this).name()));
		}

		void setAstRightN(std::shared_ptr<fAstNod> astRightN) override {
			throw std::runtime_error("Cannot set right operand for " + std::string(typeid(*this).name()));
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, EnclsScope s) override;
		 std::string toString() const override;
	};

} // namespace zebra::ast::node

