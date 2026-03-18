#pragma once

#include "ast/node/fAstOprndNod.hpp"

#include "parse/ZGrmrProdE.hpp"
#include "parse/fAst.hpp"
#include "util/fCommon.hpp"

#include <memory>

namespace zebra::ast::node {

	using parse::ZGrmrProdE;
	using util::sp;

	class fAstProdSubTreeN : public fAstOprndNod {
	private:
		ZGrmrProdE gp;
		sp<fAstRootOptrNod> rootOpNod;

	public:
		fAstProdSubTreeN(ZGrmrProdE gp, sp<fAstRootOptrNod>&& rootOp)
			 : gp(gp), rootOpNod(std::move(rootOp)) {
		}
		virtual ~fAstProdSubTreeN() = default;

		sp<fAstRootOptrNod> getRootOpNod()  {
			return rootOpNod;
		}

		ZGrmrProdE getGp() const {
			return gp;
		}
		
		void accept(sp<fAstNodVisitor> visitor, symbol::esc s) override;

		std::string toString() const override;
	};

} // namespace com::flint::compiler::frontend::ast::nodes::leaves::node::subtree
