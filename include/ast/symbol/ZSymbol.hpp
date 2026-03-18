#pragma once

#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::symbol {

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;


	class ZSymbol {
	public:
		virtual ~ZSymbol() = default;
	};

	class ZTypeParam: public ZSymbol {
	public:
		virtual ~ZTypeParam() = default;
	};

	class ZVariantTypeParam: public ZTypeParam {
	};



	class ZTrait: public ZSymbol {

	};

	class ZClass : public ZTrait {
		// sp<ZClass> parentClass_;
		// sp<std::vector<sp<ZTrait>>> traits_;
		// std::vector<sp<ZVariantTypeParam>> variantTypeParams_;
		// public:
	};

}