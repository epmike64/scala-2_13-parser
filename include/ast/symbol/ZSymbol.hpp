#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>

#include "ZSymbol.hpp"

namespace zebra::ast::symbol {
	class ZProdSubTreeN;

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
		const ZLangConstruct langConstruct_;

	public:
		ZSymbol(ZLangConstruct c) :  langConstruct_(c){}
		virtual ~ZSymbol() = default;
		ZLangConstruct getZLangConstruct() {
			return langConstruct_;
		}
	};

	class ZUnit : public ZSymbol {
	protected:
		const ZId zId_;
	public:
		ZUnit(ZId zId, ZLangConstruct c) : zId_(zId), ZSymbol(c)  {}
		~ZUnit() override = default;
	};


	class ZImport : public ZSymbol {
		PVec<std::string> imports_;
	public:
		ZImport() : ZSymbol(Z_IMPORT) {}
		void addImport(std::string im) {
			if (imports_ == nullptr) {
				imports_ = ms<std::vector<std::string>>();
			}
			imports_->push_back(std::move(im));
		}
	};

	class IHaveImport {
	public:
		virtual ~IHaveImport() = default;
		virtual sp<ZImport> getZImport() = 0;
		virtual void addImport(std::string im) = 0;
		virtual void addImports(sp<std::vector<std::string>> ims) = 0;
	};

	class ZTrait: public IHaveImport, public ZUnit {
		sp<ZImport> Import_;
	public:
		ZTrait(ZId zId) : ZUnit(std::move(zId), Z_TRAIT) {}
		ZTrait(ZId zId, ZLangConstruct c) : ZUnit(std::move(zId), c) {}
		sp<ZImport> getZImport() override {
			return Import_;
		}
		void addImport(std::string im) override{
			if (Import_ == nullptr) {
				Import_ = ms<ZImport>();
			}
			Import_->addImport(std::move(im));
		}
		void addImports(sp<std::vector<std::string>> ims) override {
			if (Import_ == nullptr) {
				Import_ = ms<ZImport>();
			}
			for (const auto& im : *ims) {
				Import_->addImport(im);
			}
		}
	};

	class ZDecl: public ZUnit {
	public:
		ZDecl(ZId zId) : ZUnit(std::move(zId), Z_DECL) {}
		// ...existing code...
	};

	class ZFunc: public ZUnit {
	public:
		ZFunc(ZId zId) : ZUnit(std::move(zId), Z_FUNC) {}
	};

	class ZTreePostOrderSS {
		PVecP<fAstNod> postOrderSS;
	public:
		ZTreePostOrderSS(PVecP<fAstNod> postOrderSS) : postOrderSS(std::move(postOrderSS)) {}
	};

	class ZProdSubTreeN: public ZUnit {
	protected:
		sp<ZTreePostOrderSS> postOrderSS_;
		public:
		ZProdSubTreeN(ZId zId) : ZUnit(std::move(zId), Z_PROD_SUB_TREE_NOD) {}
		ZProdSubTreeN(ZId zId, ZLangConstruct c) : ZUnit(std::move(zId), c) {}

		void setTreePostOrderSS(sp<ZTreePostOrderSS> ztp) {
			postOrderSS_ = ztp;
		}

		sp<ZTreePostOrderSS> getTreePostOrderSS() const {
			return postOrderSS_;
		}
	};

	class ZType : public ZProdSubTreeN {
	public:
		ZType(ZId zId) : ZProdSubTreeN(std::move(zId), Z_TYPE) {}
		ZType(ZId zId, ZLangConstruct c) : ZProdSubTreeN(std::move(zId), c) {}

		void setZType(sp<ZTreePostOrderSS> ss) {
			postOrderSS_ = ss;
		}

		sp<ZTreePostOrderSS> getZType() const {
			return postOrderSS_;
		}
	};

	class ZParamType: public ZType {
		public:
		ZParamType(ZId zId) : ZType(std::move(zId), Z_PARAM_TYPE) {}
		ZParamType(ZId zId, ZLangConstruct c) : ZType(std::move(zId), c) {}

	};


	class ZClassParam: public ZParamType {
	protected:
		const bool isMutable_;
		sp<ZTreePostOrderSS> defaultExpr_;
	public:
		ZClassParam(ZId zId, bool isMutable) : ZParamType(std::move(zId), Z_CLASS_PARAM), isMutable_(isMutable) {}
		ZClassParam(ZId zId, ZLangConstruct c, bool isMutable) : ZParamType(std::move(zId), c), isMutable_(isMutable) {}

		void setDefaultExpr(sp<ZTreePostOrderSS> de) {
			defaultExpr_ = de;
		}
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
		ZClass(ZId zId) : ZTrait(std::move(zId), Z_CLASS) {}

	};

	class ZProgram: public ZUnit {
		public:
		ZProgram(ZId zId) : ZUnit(std::move(zId), Z_PROGRAM) {}
	};

	class ZCompileUnit: public ZUnit {
		std::string packgName_;
		PVecP<ZClass> classes_;
	public:
		ZCompileUnit(ZId zId) : ZUnit(std::move(zId), Z_COMPILATION_UNIT) {
			packgName_ = "_ROOT_PKG_";
		}
		void setPackage(std::string n) {
			packgName_ += "." + n;
		}

		void addClass(sp<ZClass> cls) {
			if (classes_ == nullptr) {
				classes_ = ms<std::vector<std::shared_ptr<ZClass>>>();
			}
			classes_->push_back(cls);
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
