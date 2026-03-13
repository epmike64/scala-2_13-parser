#pragma once

#include <memory>

namespace zebra::ast::node {

	class EnclosingScope;
	using esc = std::shared_ptr<EnclosingScope>;

	class EnclosingScope {
		esc parentScope_;
		public:
		EnclosingScope() = default;
		virtual ~EnclosingScope() = default;

		void setParentScope(esc parentScope);
		esc getParentScope();
	};



	//esc
}