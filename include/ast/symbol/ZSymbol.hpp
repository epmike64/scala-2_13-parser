#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>

namespace zebra::ast::symbol {

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;

	class ZId {
	protected:
		std::string qualId_;
	public:
		ZId(std::string qId) : qualId_(std::move(qId)) {}
		ZId(const ZId&) = default;
		ZId(ZId&&) = default;
		ZId& operator=(const ZId&) = default;
		ZId& operator=(ZId&&) = default;

		const std::string& qualId() const { return qualId_; }

		bool operator==(const ZId& other) const {
			return qualId_ == other.qualId_;
		}
	};

	class ZSymbol {
	protected:
		const ZId zId_;
	public:
		ZSymbol(ZId zId) : zId_(std::move(zId)) {}
		virtual ~ZSymbol() = default;
		virtual  ZLangConstruct langConstruct() = 0;
		const ZId zId() const { return zId_; }
	};

	class ZTypeParam: public ZSymbol {
	public:
		ZTypeParam(ZId zId) : ZSymbol(std::move(zId)) {}
		// ...existing code...
	};

	class ZTrait: public ZSymbol {
	public:
		ZTrait(ZId zId) : ZSymbol(std::move(zId)) {}
		// ...existing code...
	};

	class ZDecl: public ZSymbol {
	public:
		ZDecl(ZId zId) : ZSymbol(std::move(zId)) {}
		// ...existing code...
	};

	class ZFunc: public ZSymbol {
	public:
		ZFunc(ZId zId) : ZSymbol(std::move(zId)) {}
		ZLangConstruct langConstruct() override {
			return Z_FUNC;
		}
	};

	class ZClassParam: public ZSymbol {
	public:
		ZClassParam(ZId zId) : ZSymbol(std::move(zId)) {}
		ZLangConstruct langConstruct() override {
			return Z_CLASS_PARAM;
		}
	};

	class ZClassConstr: public ZSymbol {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr(ZId zId) : ZSymbol(std::move(zId)) {}
		ZLangConstruct langConstruct() override {
			return Z_CLASS_CONSTR;
		}
	};

	class ZCompileUnit: public ZSymbol {
	protected:
		PVecP<ZClass> classes_;
		std::vector<std::string> pkgName_;
	public:
		ZCompileUnit(ZId zId) : ZSymbol(std::move(zId)) {}
	};

	class ZClass : public ZTrait {
		sp<ZClass> parentClass_;
		PVecP<ZTrait> traits_;
		PVecP<ZTypeParam> typeParams_;
		PVecP<ZClassConstr> constrs_;
		PVecP<ZDecl> decls_;
		PVecP<ZFunc> funcs_;
	public:
		ZClass(ZId zId) : ZTrait(std::move(zId)) {}
		ZLangConstruct langConstruct() override {
			return Z_CLASS;
		}
	};

}

namespace std {
	template <>
	struct hash<zebra::ast::symbol::ZId> {
		std::size_t operator()(const zebra::ast::symbol::ZId& id) const noexcept {
			return std::hash<std::string>{}(id.qualId());
		}
	};
}
