#pragma once

#include "ast/node/fAstOprndNod.hpp"

#include "parse/fLangGrmrProdE.hpp"
#include "parse/fAst.hpp"
#include "util/fCommon.hpp"

#include <memory>

namespace zebra::ast::node {

	using parse::fLangGrmrProdE;
	using util::sp;

	class fAstProdSubTreeN : public fAstOprndNod {
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
		
		void accept(sp<fAstNodVisitor> visitor, symbol::esc s) override;

		std::string toString() const override;
	};

} // namespace com::flint::compiler::frontend::ast::nodes::leaves::node::subtree
