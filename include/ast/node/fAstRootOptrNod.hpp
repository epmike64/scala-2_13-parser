#pragma once

#include "ast/node/fAstOptrNod.hpp"
#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstNodKndE.hpp"

#include <memory>
#include <stdexcept>

namespace zebra::ast::node {

	using lex::kind::fLangOperatorKind;

	class fAstRootOptrNod : public fAstOptrNod {
	public:
		fAstRootOptrNod()
			 : fAstOptrNod(fLangOperatorKind::O_INTERN_ROOT, &fToken::ROOT_OPERATOR) {
		}

		void setAstLeftN(std::shared_ptr<fAstNod> astLeftN) override {
			throw std::runtime_error("Invalid operation");
		}

		fAstNodKndE astNKndE() override {
			return fAstNodKndE::AST_ROOT_OPERATOR;
		}
	};

} // namespace com::flint::compiler::frontend::ast::nodes::operators
