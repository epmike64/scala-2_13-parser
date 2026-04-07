#pragma once
#include "util/fCommon.hpp"

namespace zebra::ast::symbol {

	using namespace zebra::util;

	class XEnclSc {
	protected:
		const sp<XEnclSc> parentScope_;
	public:
		XEnclSc(sp<XEnclSc> parentScope);
		sp<XEnclSc> getParentScope();
	};

	using EncSc = std::shared_ptr<XEnclSc>;
}
