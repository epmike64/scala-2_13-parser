#pragma once

#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"

namespace zebra::ast::symbol {

	enum ZLangConstruct {
		Z_TYPE_PARAM,
		Z_VARIANT_TYPE_PARAM,
		Z_TRAIT,

		Z_CLASS,


	};
}