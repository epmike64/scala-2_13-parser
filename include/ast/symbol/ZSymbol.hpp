#pragma once

#include "ZLangConstruct.hpp"
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
		virtual  ZLangConstruct langConstruct() = 0;
	};

	class ZTypeParam: public ZSymbol {
	public:
		virtual ~ZTypeParam() = default;
		ZLangConstruct langConstruct() override {
			return Z_TYPE_PARAM;
		}
	};

	class ZVariantTypeParam: public ZTypeParam {
		sp<fVariantTypeParam> n;
		public:
			ZVariantTypeParam(sp<fVariantTypeParam> n);
		  ZLangConstruct langConstruct() override {
			  return Z_VARIANT_TYPE_PARAM;
		  }
	};

	class ZTrait: public ZSymbol {
	public:

		ZLangConstruct langConstruct() override {
			return Z_TRAIT;
		}
	};

	class ZDecl: public ZSymbol {
		public:
		ZLangConstruct langConstruct() override {
			return Z_DECL;
		}
	};

	class ZFunc: public ZSymbol {
		public:
		ZLangConstruct langConstruct() override {
			return Z_FUNC;
		}
	};

	class ZClass : public ZTrait {
		sp<ZClass> parentClass_;
		PVecP<ZTrait> traits_;
		PVecP<ZVariantTypeParam> variantTypeParams_;
		PVecP<ZTypeParam> typeParams_;
		PVecP<ZDecl> decls_;
		PVecP<ZFunc> funcs_;

		public:
		ZLangConstruct langConstruct() override {
			return Z_CLASS;
		}
	};

}