#pragma once

#include "parse/fLangGrmrProdE.hpp"
#include "parse/fAst.hpp"
#include "util/fCommon.hpp"

#include <memory>

#include "ast/fLangOperand.hpp"

namespace zebra::ast::node {

	using parse::fLangGrmrProdE;
	using util::sp;

	class fAstProdSubTreeN : public fLangOprnd {
	private:
		fLangGrmrProdE gp;
		sp<fAstRootOptrNod> rootOpNod;

	public:
		fAstProdSubTreeN(fLangGrmrProdE gp, sp<fAstRootOptrNod>&& rootOp)
			 : gp(gp), rootOpNod(std::move(rootOp)) {
		}
		virtual ~fAstProdSubTreeN() = default;

		sp<fAstRootOptrNod> getRootOpNod()  {
			return rootOpNod;
		}

		fLangGrmrProdE getGp() const {
			return gp;
		}
		
		void accept(sp<fAstNodVisitor> visitor, symbol::ssc s) override;

		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::PROD_SUB_TREE_N;
		}
	};

} // namespace com::flint::compiler::frontend::ast::nodes::leaves::node::subtree
