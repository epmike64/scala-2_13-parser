#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>


namespace zebra::ast::symbol {
	class ZParam;
	class ZProdSubTreeN;

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;

	class ZId {
	protected:
		std::string qualId_;
	public:
		explicit ZId(std::string qId) : qualId_(std::move(qId)) {}
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
		explicit ZSymbol(ZLangConstruct c) :  langConstruct_(c){}
		virtual ~ZSymbol() = default;
		ZLangConstruct getZLangConstruct() {
			return langConstruct_;
		}
	};

	class I_ZId {
	protected:
		const ZId zId_;
		public:
		explicit I_ZId(ZId zId) : zId_(std::move(zId)) {}
		explicit I_ZId(std::string s): zId_(std::move(ZId(std::move(s)))) {}
		const ZId& getZId() const {
			return zId_;
		}
	};

	class ZIdSymbol : public  I_ZId, public ZSymbol {
	public:
		//ZIdSymbol(ZId zId, ZLangConstruct c) : I_ZId(std::move(zId)), ZSymbol(c)  {}
		ZIdSymbol(std::string sid, ZLangConstruct c) : I_ZId(std::move(sid)), ZSymbol(c)  {}
		~ZIdSymbol() override = default;
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

	class I_Imports {
	public:
		virtual ~I_Imports() = default;
		virtual sp<ZImport> getZImport() = 0;
		virtual void addImport(std::string im) = 0;
		virtual void addImports(sp<std::vector<std::string>> ims) = 0;
	};

	class ZTrait: public I_Imports, public ZIdSymbol {
		sp<ZImport> Import_;
	public:
		explicit ZTrait(std::string sId) : ZIdSymbol(std::move(sId), Z_TRAIT) {}
		ZTrait(std::string sId, ZLangConstruct c) : ZIdSymbol(std::move(sId), c) {}
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

	class ZFunc : public ZSymbol {
	protected:
		PVecP<ZParam> params_;
	public:
		ZFunc(ZLangConstruct c) : ZSymbol(c) {}
		void addParam(sp<ZParam> p) {
			if (params_ == nullptr) {
				params_ = ms<std::vector<std::shared_ptr<ZParam>>>();
			}
			params_->push_back(p);
		}
	};

	class ZRegFunc: public I_ZId, public ZFunc {
	public:
		explicit ZRegFunc(std::string sid) : I_ZId(std::move(sid)), ZFunc(Z_REG_FUNC) {}
		ZRegFunc(std::string sid, ZLangConstruct c) : I_ZId(std::move(sid)), ZFunc(c) {}
	};

	class ZThisFunc: public ZFunc{
	public:
		ZThisFunc() : ZFunc(Z_THIS_FUNC) {}
	};

	class ZTreePostOrderSS {
		std::vector<sp<fAstNod>> postOrderSS_;
	public:
		bool empty() {
			return postOrderSS_.empty();
		}
		void push_back(sp<fAstNod> n) {
			postOrderSS_.push_back(n);
		}
	};

	class ZProdSubTreeN: public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> postOrderSS_;
		public:
		ZProdSubTreeN() : ZSymbol(Z_PROD_SUB_TREE_NOD) {}
		explicit ZProdSubTreeN(ZLangConstruct c) : ZSymbol(c) {}

		sp<ZTreePostOrderSS> getTreePostOrderSS() {
			if (postOrderSS_ == nullptr) {
				postOrderSS_ = ms<ZTreePostOrderSS>();
			}
			return postOrderSS_;
		}
	};

	class ZType : public ZProdSubTreeN {
	public:
		ZType(): ZProdSubTreeN( Z_TYPE) {}
		explicit ZType(ZLangConstruct c) : ZProdSubTreeN(c) {}
		sp<ZTreePostOrderSS> getZType() const {
			return postOrderSS_;
		}
	};

	class ZParamType: public ZType {
		public:
		ZParamType() : ZType(Z_PARAM_TYPE) {}
		explicit ZParamType(ZLangConstruct c) : ZType(c) {}

	};

	class ZVariantTypeParam: public ZParamType {
	public:
		ZVariantTypeParam() : ZParamType( Z_VARIANT_TYPE_PARAM) {}
		explicit ZVariantTypeParam(ZLangConstruct c) : ZParamType(c) {}
	};

	class ZParam : public I_ZId, public ZParamType {
		sp<ZTreePostOrderSS> defaultExpr_;
		public:
		explicit ZParam(std::string sid) : I_ZId(std::move(sid)), ZParamType(Z_PARAM) {}
		ZParam(std::string sid, ZLangConstruct c) : I_ZId(std::move(sid)), ZParamType(c) {}
		void setDefaultValueExpr(sp<ZTreePostOrderSS> de) {
			defaultExpr_ = de;
		}
	};

	class ZClassParam: public ZParam{
	protected:
		const bool isMutable_;
		sp<ZTreePostOrderSS> defaultExpr_;
	public:
		ZClassParam(std::string sid, bool isMutable) : ZParam(std::move(sid), Z_CLASS_PARAM), isMutable_(isMutable) {}
		ZClassParam(std::string sid, ZLangConstruct c, bool isMutable) :ZParam(std::move(sid), c), isMutable_(isMutable){}
	};

	class ZClassConstr: public ZSymbol {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr() : ZSymbol(Z_CLASS_CONSTR) {}
	};

	class ZClassDef : public ZTrait {
		sp<ZClassDef> parentClass_;
		PVecP<ZClassParam> clsParams_;
		PVecP<ZTrait> traits_;
		PVecP<ZTypeParam> typeParams_;
		PVecP<ZClassConstr> constrs_;
		// PVecP<ZDecl> decls_;
		PVecP<ZRegFunc> funcs_;
	public:
		explicit ZClassDef(std::string zId) : ZTrait(std::move(zId), Z_CLASS_DEF) {}
		void addClassParam(sp<ZClassParam> clsParam) {
			if (clsParams_ == nullptr) {
				clsParams_ = ms<std::vector<std::shared_ptr<ZClassParam>>>();
			}
			clsParams_->push_back(clsParam);
		}
	};

	class ZProgram: public ZSymbol {
		public:
		ZProgram() : ZSymbol(Z_PROGRAM) {}
	};

	class I_Stmts {
	public:
		virtual ~I_Stmts() = default;
	};

	class ZTemplateBody: I_Stmts, public ZSymbol {
	public:
		ZTemplateBody() : ZSymbol(Z_TEMPLATE_BODY) {}
	};

	class ZCompileUnit: public ZIdSymbol {
		std::string packgName_;
		PVecP<ZClassDef> classes_;
	public:
		explicit ZCompileUnit(std::string zId) : ZIdSymbol(std::move(zId), Z_COMPILATION_UNIT) {
			packgName_ = "_ROOT_PKG_";
		}
		void setPackage(std::string n) {
			packgName_ += "." + n;
		}

		void addClass(sp<ZClassDef> cls) {
			if (classes_ == nullptr) {
				classes_ = ms<std::vector<std::shared_ptr<ZClassDef>>>();
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
