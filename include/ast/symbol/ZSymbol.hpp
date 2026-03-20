#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>

#include "ZSymbol.hpp"

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

	class ZUnit : public ZSymbol {
	protected:
		PVecP<ZUnit> subUnits_;
		PVec<std::string> imports_;
		PVec<std::string> qualName_;
	public:
		explicit ZUnit(ZId zId) : ZSymbol(std::move(zId)) {}
		~ZUnit() override = default;
		virtual void addSubUnit(sp<ZUnit> subUnit) = 0;
		virtual void addImport(std::string import_) = 0;
		virtual void addQualName(std::string qualName) = 0;
	};


	class ZTypeParam: public ZSymbol {
	public:
		ZTypeParam(ZId zId) : ZSymbol(std::move(zId)) {}
		// ...existing code...
	};

	class ZTrait: public ZUnit {
	public:
		ZTrait(ZId zId) : ZUnit(std::move(zId)) {}
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


	class ZCompileUnit: public ZUnit {
	public:
		ZCompileUnit(ZId zId) : ZUnit(std::move(zId)) {
			qualName_ = std::make_shared<std::vector<std::string>>();
			qualName_->emplace_back("_ROOT_PKG_");
		}
		void addSubUnit(sp<ZUnit> subUnit) override {
			subUnits_->emplace_back(std::move(subUnit));
		}
		void addImport(std::string import_) override {
			imports_->emplace_back(std::move(import_));
		}
		void addQualName(std::string qualName) override {
			 qualName_->emplace_back(std::move(qualName));
		}

		void addSubPackage(std::string n) {
			addQualName(n);
		}

		void addClass(sp<ZClass> cls) {
			addSubUnit(cls);
		}

		ZLangConstruct langConstruct() override {
			return Z_COMPILATION_UNIT;
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
