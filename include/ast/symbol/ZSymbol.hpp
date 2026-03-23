#pragma once

#include "ZLangConstruct.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fType.hpp"
#include <functional>

#include "ZSymbol.hpp"


namespace zebra::ast::symbol {
	class ZBlock;
	class ZParam;
	class ZTypeParamList;
	class ZTypeParam;
	class ZProdSubTreeN;
	class ZVariantTypeParam;

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
		std::vector<std::string> imports_;
	public:
		ZImport() : ZSymbol(Z_IMPORT) {}
		void addImport(std::string im) {
			imports_.push_back(std::move(im));
		}
		void addImport(std::vector<std::string> im) {
			imports_.insert(imports_.end(), std::make_move_iterator(im.begin()), std::make_move_iterator(im.end()));
		}
	};




	class ZFunc : public virtual ZSymbol {
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



	class ZThisFunc: public ZFunc{
	public:
		ZThisFunc() : ZSymbol(Z_THIS_FUNC_DEF), ZFunc(Z_THIS_FUNC_DEF) {}
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
		std::string toString() const{
			std::stringstream out;
			out << "PostOrderSS: [";
			for (const auto& nod : postOrderSS_) {
				out << (nod ? nod->toString() : "null") << ", ";
			}
			out << "]";
			return out.str();
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
		~ZParamType() override = default;
	};



	class ZTypeParamList: public virtual ZSymbol {
	protected:
		vecP<ZTypeParam> typeParams_;
		explicit ZTypeParamList(ZLangConstruct c) : ZSymbol(c) {}
	public:
		ZTypeParamList() : ZSymbol(Z_TYPE_PARAM_ARGS) {}
		~ZTypeParamList() override = default;

		void addTypeParam(sp<ZTypeParam> tp) {
			typeParams_.push_back(tp);
		}
		void addTypeParams(vecP<ZTypeParam> tps) {
			typeParams_.insert(typeParams_.end(), tps.begin(), tps.end());
		}
	};

	class ZTypeParam: public ZId, public ZTypeParamList {
	public:
		explicit ZTypeParam(std::string zId) : ZSymbol(Z_TYPE_PARAM), ZId(std::move(zId)), ZTypeParamList(Z_TYPE_PARAM) {}
		ZTypeParam(std::string zId, ZLangConstruct c) : ZSymbol(c), ZId(std::move(zId)), ZTypeParamList(c) {}
		~ZTypeParam() override = default;
	};

	class ZVariantTypeParam: public ZTypeParam {
	protected:
		const fVarianceE variance_;
	public:
		ZVariantTypeParam(std::string sid, fVarianceE v) : ZSymbol(Z_VARIANT_TYPE_PARAM), variance_(v), ZTypeParam(sid, Z_VARIANT_TYPE_PARAM) {}
		explicit ZVariantTypeParam(std::string sid, fVarianceE v, ZLangConstruct c) : ZSymbol(c), variance_(v), ZTypeParam(sid, c) {}
		~ZVariantTypeParam() override = default;
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

	class ZImportList: public virtual ZSymbol{
		vecP<ZImport> imports_;
	public:
		ZImportList() : ZSymbol(Z_IMPORT_LIST) {}
		~ZImportList() override = default;
		void addImport(sp<ZImport> im) {
			imports_.push_back(im);
		}
	};

	class ZRegFunc: public I_ZId, public ZFunc, public ZTypeParamList {
	protected:
		sp<ZType> returnType_;
		sp<ZProdSubTreeN> funBodyExpr_;
		sp<ZBlock> funBodyBlock_;

		public:
		explicit ZRegFunc(std::string sid) : ZSymbol(Z_REG_FUNC_DEF), I_ZId(std::move(sid)), ZFunc(Z_REG_FUNC_DEF), ZTypeParamList(Z_REG_FUNC_DEF) {}
		ZRegFunc(std::string sid, ZLangConstruct c) : ZSymbol(c), I_ZId(std::move(sid)), ZFunc(c), ZTypeParamList(c) {}

		~ZRegFunc() override = default;
		void setReturnType(sp<ZType> t) {
			returnType_ = t;
		}
		void setFunBodyExpr(sp<ZProdSubTreeN> e) {
			funBodyExpr_ = e;
		}
		void setFunBodyBlock(sp<ZBlock> b) {
			funBodyBlock_ = b;
		}
	};

	class ZTraitDef: public ZId, public ZTypeParamList, public ZImportList {

	public:
		explicit ZTraitDef(std::string sId) : ZSymbol(Z_TRAIT_DEF), ZId(std::move(sId)), ZTypeParamList(Z_TRAIT_DEF) {}
		ZTraitDef(std::string sId, ZLangConstruct c) : ZSymbol(c), ZId(std::move(sId)), ZTypeParamList(c) {}
	};


	class ZClassParam: public ZParam{
	protected:
		const bool isMutable_;
		sp<ZTreePostOrderSS> defaultExpr_;
	public:
		ZClassParam(std::string sid, bool isMutable) : ZParam(std::move(sid), Z_CLASS_PARAM), isMutable_(isMutable) {}
		ZClassParam(std::string sid, ZLangConstruct c, bool isMutable) :ZParam(std::move(sid), c), isMutable_(isMutable){}
	};

	class ZBlock: public ZSymbol {
		vecP<ZSymbol> stmts_;
		public:
		ZBlock() : ZSymbol(Z_BLOCK) {}
		void addStmt(sp<ZSymbol> stmt) {
			stmts_.push_back(stmt);
		}
	};

	class ZClassConstr: public ZSymbol {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr() : ZSymbol(Z_CLASS_CONSTR) {}
	};



	class ZObjectDef: public ZId, public ZSymbol {
		public:
		explicit ZObjectDef(std::string zId) : ZId(std::move(zId)), ZSymbol(Z_OBJECT_DEF) {}
	};

	class ZClassDef : public ZTraitDef {
		sp<ZClassDef> parentClass_;
		PVecP<ZClassParam> clsParams_;
		PVecP<ZTraitDef> traits_;
		// sp<ZTypeParamList> typeParams_;
		PVecP<ZClassConstr> constrs_;
		// PVecP<ZDecl> decls_;
		PVecP<ZRegFunc> funcs_;
	public:
		explicit ZClassDef(std::string zId) : ZSymbol(Z_CLASS_DEF), ZTraitDef(std::move(zId), Z_CLASS_DEF) {}
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
