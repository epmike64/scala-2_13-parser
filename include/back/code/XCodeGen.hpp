#pragma once

#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"
#include "ast/symbol/ZSymbol.hpp"
namespace zebra::back::code {

	using namespace zebra::back;
	using namespace zebra::ast::symbol;

	class XCodeGen {
	protected:
		sp<ZProgram> zProgram_;
		public:
		explicit XCodeGen(ast::node::sp<ast::symbol::ZProgram> zProgram);
		void gen();
	};
}