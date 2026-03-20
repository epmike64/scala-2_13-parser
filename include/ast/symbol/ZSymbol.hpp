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
		const ZLangConstruct langConstruct_;

	public:
		explicit ZUnit(ZId zId, ZLangConstruct c) : ZSymbol(std::move(zId)),  langConstruct_(c) {}
		~ZUnit() override = default;

		void addSubUnit(sp<ZUnit> subUnit)  {
			subUnits_->emplace_back(std::move(subUnit));
		}
		void addImport(std::string import_) {
			imports_->emplace_back(std::move(import_));
		}
		void addQualName(std::string qualName) {
			qualName_->emplace_back(std::move(qualName));
		}

		ZLangConstruct langConstruct() override {
			return langConstruct_;
		}
	};


	class ZTypeParam: public ZSymbol {
	public:
		ZTypeParam(ZId zId) : ZSymbol(std::move(zId)) {}
		// ...existing code...
	};

	class ZTrait: public ZUnit {
	public:
		ZTrait(ZId zId) : ZUnit(std::move(zId), ZLangConstruct::Z_TRAIT) {}
		// ...existing code...
	};

	class ZDecl: public ZUnit {
	public:
		ZDecl(ZId zId) : ZUnit(std::move(zId), Z_DECL) {}
		// ...existing code...
	};

	class ZFunc: public ZUnit {
	public:
		ZFunc(ZId zId) : ZUnit(std::move(zId), Z_FUNC) {}
		ZLangConstruct langConstruct() override {
			return Z_FUNC;
		}
	};

	class ZClassParam: public ZUnit {
	public:
		ZClassParam(ZId zId) : ZUnit(std::move(zId), Z_CLASS_PARAM) {}
	};

	class ZClassConstr: public ZUnit {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr(ZId zId) : ZUnit(std::move(zId), Z_CLASS_CONSTR) {}
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

	class ZProgram: public ZUnit {
		public:
		ZProgram(ZId zId) : ZUnit(std::move(zId), Z_PROGRAM) {}
	};

	class ZCompileUnit: public ZUnit {
	public:
		ZCompileUnit(ZId zId) : ZUnit(std::move(zId), Z_COMPILATION_UNIT) {
			qualName_ = std::make_shared<std::vector<std::string>>();
			qualName_->emplace_back("_ROOT_PKG_");
		}
		void addSubPackage(std::string n) {
			addQualName(n);
		}

		void addClass(sp<ZClass> cls) {
			addSubUnit(cls);
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
