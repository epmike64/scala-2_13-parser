#pragma once
#include <string>


namespace zebra::ast::symbol {

	class ZError {
		public:
		virtual ~ZError() = default;
	};

	class ZPos {
	public:
		const int lineno_, colno_;
		ZPos(const int lineno, const int colno) : lineno_(lineno), colno_(colno) {}
	};

	class ZErrorMessage : public ZError {
	protected:
		std::string errorMessage;
		PVecP<ZPos> errPos;
	public:
		ZErrorMessage(const std::string& errorMessage) : errorMessage(errorMessage) {}
	};
}
