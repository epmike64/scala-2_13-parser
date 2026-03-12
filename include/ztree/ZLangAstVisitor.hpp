#pragma once
#include "ast/node/fLangAstVisitor.hpp"

namespace zbit::ztree {

	using namespace ast::leaf;
	using namespace zebra::ast::node;

	class ZTreeBuildAstVisitor: public fLangAstVisitor, public std::enable_shared_from_this<ZTreeBuildAstVisitor> {
	public:
		ZTreeBuildAstVisitor(sp<fCompileUnit> cu) : fLangAstVisitor(cu) {}
	};
}
