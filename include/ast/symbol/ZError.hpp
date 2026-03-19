#pragma once
#include <string>
#include <vector>
#include "lex/token/fToken.hpp"

namespace zebra::ast::symbol {

	using zebra::lex::token::fTokenLocation;

	class ZError {
		public:
		virtual ~ZError() = default;
	};


	class ZErrorMessage : public ZError {
	protected:
		std::string errorMessage;
		PVecP<const fTokenLocation*> tokErrorLocs_;
	public:
		ZErrorMessage(const std::string& errorMessage) : errorMessage(errorMessage) {}
	};
}
