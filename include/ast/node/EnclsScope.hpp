#pragma once

#include <memory>

namespace zebra::ast::node {


	class EnclosingScope {
		public:
		EnclosingScope() = default;
		virtual ~EnclosingScope() = default;
	};

	using esc = std::shared_ptr<EnclosingScope>;


	//esc
}