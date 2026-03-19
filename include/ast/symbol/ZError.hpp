#pragma once
#include <string>


namespace zebra::ast::symbol {

	class ZError {
		public:
		virtual ~ZError() = default;
	};

	class ZErrorMessage : public ZError {
	protected:
		std::string errorMessage;
	public:
		ZErrorMessage(const std::string& errorMessage) : errorMessage(errorMessage) {}
	};
}
