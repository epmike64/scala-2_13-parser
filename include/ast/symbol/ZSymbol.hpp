#pragma once

#include "ZLangConstruct.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "ast/node/fAstNod.hpp"
#include "util/fCommon.hpp"
#include <functional>
#include <sstream>
#include <string>
#include <vector>



namespace zebra::ast::symbol {
	class ZBlock;
	class ZParam;
	class ZTypeParamList;
	class ZTypeParam;
	class ZProdSubTreeN;
	class ZVariantTypeParam;

	using namespace zebra::ast::node;
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



	class ZThisFunc: public ZFunc{
	public:
		ZThisFunc() : ZFunc(Z_THIS_FUNC_DEF){}
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
		const sp<ZTreePostOrderSS> postOrderSS_ = ms<ZTreePostOrderSS>();
		public:
		ZProdSubTreeN() : ZSymbol(Z_PROD_SUB_TREE_NOD) {}
		explicit ZProdSubTreeN(ZLangConstruct c) : ZSymbol(c) {}

		sp<ZTreePostOrderSS> getTreePostOrderSS() const {
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

	class Zif: public ZSymbol {
	protected:
		sp<ZProdSubTreeN> condExpr_;
		sp<ZProdSubTreeN> bodyExpr_;
		sp<ZProdSubTreeN> elseBodyExpr_;
	public:
		Zif() : ZSymbol(Z_IF) {}
		void setCondExpr(sp<ZProdSubTreeN> p) {
			condExpr_ = p;
		}
		void setBody(sp<ZProdSubTreeN> p) {
			bodyExpr_ = p;
		}
		void setElseBody(sp<ZProdSubTreeN> p) {
			elseBodyExpr_ = p;
		}
	};

	class ZModifiers: public ZSymbol {
		std::vector<std::string> modifiers_;
		public:
		ZModifiers() : ZSymbol(Z_MODIFIERS) {}
	};

	class ZWhile: public ZSymbol {
	protected:
		sp<ZProdSubTreeN> condExpr_;
		sp<ZProdSubTreeN> bodyExpr_;
	public:
		ZWhile() : ZSymbol(Z_WHILE) {}
		void setCondExpr(sp<ZProdSubTreeN> p) {
			condExpr_ = p;
		}
		void setBody(sp<ZProdSubTreeN> p) {
			bodyExpr_ = p;
		}
	};

	class ZValueDcl: public ZSymbol {
		sp<ZModifiers> modifiers_;
		sp<ZType> type_;
		sp<ZProdSubTreeN> assignExpr_;
		vecP<ZProdSubTreeN> names_ = vecP<ZProdSubTreeN>();
		public:
		ZValueDcl() : ZSymbol(Z_VALUE_DCL) {}
		void setModifiers(sp<ZModifiers> m) {
			modifiers_ = m;
		}
		void setType(sp<ZType> t) {
			type_ = t;
		}
		void setAssignExpr(sp<ZProdSubTreeN> e) {
			assignExpr_ = e;
		}
		void addName(sp<ZProdSubTreeN> n) {
			names_.push_back(n);
		}
	};

	class ZParamType: public ZType {
		public:
		ZParamType() : ZType(Z_PARAM_TYPE) {}
		explicit ZParamType(ZLangConstruct c) : ZType(c) {}
		~ZParamType() override = default;
	};

	class ZTypeParamList: public ZSymbol {
	protected:
		vecP<ZTypeParam> typeParams_;
	public:
		ZTypeParamList() : ZSymbol(Z_TYPE_PARAMS) {}
		~ZTypeParamList() override = default;

		void addTypeParam(sp<ZTypeParam> tp) {
			typeParams_.push_back(tp);
		}
		void addTypeParams(vecP<ZTypeParam> tps) {
			typeParams_.insert(typeParams_.end(), tps.begin(), tps.end());
		}
	};

	class ZVariantTypeParamList: public ZSymbol {
	protected:
		vecP<ZVariantTypeParam> typeParams_;
	public:
		ZVariantTypeParamList() : ZSymbol(Z_VARIANT_TYPE_PARAMS) {}
		~ZVariantTypeParamList() override = default;

		void addVariantTypeParam(sp<ZVariantTypeParam> tp) {
			typeParams_.push_back(tp);
		}
	};


	class ZTypeParam: public ZIdSymbol{
	protected:
		sp<ZVariantTypeParamList> variantTypeParamList_;
	public:
		explicit ZTypeParam(std::string zId) : ZIdSymbol(std::move(zId), Z_TYPE_PARAM){}
		ZTypeParam(std::string zId, ZLangConstruct c) : ZIdSymbol(std::move(zId), c){}
		~ZTypeParam() override = default;

		void setVariantTypeParamList(sp<ZVariantTypeParamList> vtpList) {
			variantTypeParamList_ = vtpList;
		}
		sp<ZVariantTypeParamList> getVariantTypeParamList() {
			return variantTypeParamList_;
		}
	};

	class ZVariantTypeParam: public ZSymbol{
	protected:
		const fVarianceE variance_;
		sp<ZTypeParam> typeParam_;
	public:
		explicit ZVariantTypeParam(fVarianceE v) : ZSymbol(Z_VARIANT_TYPE_PARAM), variance_(v) {}
		ZVariantTypeParam(fVarianceE v, ZLangConstruct c) : ZSymbol(c), variance_(v) {}
		~ZVariantTypeParam() override = default;
		void setTypeParam(sp<ZTypeParam> tp) {
			typeParam_ = tp;
		}
		sp<ZTypeParam> getTypeParam() {
			return typeParam_;
		}

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

	class ZClassParents: public ZSymbol {
		sp<ZType> type_;
	public:
		ZClassParents() : ZSymbol(Z_CLASS_PARENTS) {}
		~ZClassParents() override = default;
		void setType(sp<ZType> t) {
			type_ = t;
		}
	};

	class ZStmtList: public ZSymbol {
	protected:
		PVecP<ZSymbol> statements_;
	public:
		ZStmtList() : ZSymbol(Z_STMT_LIST) {}
		ZStmtList(ZLangConstruct c) : ZSymbol(c) {}
		~ZStmtList() override = default;

		void addStmt(sp<ZSymbol> stmt) {
			if (statements_ == nullptr) {
				statements_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
			}
			statements_->push_back(stmt);
		}
		PVecP<ZSymbol> getStmts() {
			return statements_;
		}
	};

	class ZRegFunc: public ZId, public ZFunc {
	protected:
		sp<ZTypeParamList> typeParamList_;
		sp<ZType> returnType_;
		sp<ZProdSubTreeN> funBodyExpr_;
		sp<ZBlock> funBodyBlock_;

		public:
		explicit ZRegFunc(std::string sid) : ZId(std::move(sid)), ZFunc(Z_REG_FUNC_DEF){}
		ZRegFunc(std::string sid, ZLangConstruct c) : ZId(std::move(sid)), ZFunc(c) {}

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

		void setTypeParamList(sp<ZTypeParamList> tps) {
			typeParamList_ = tps;
		}

		sp<ZTypeParamList> getTypeParamList() {
			return typeParamList_;
		}
	};

	class ZTraitDef: public ZIdSymbol {
		protected:

		sp<ZVariantTypeParamList> variantTypeParamList_;
	public:
		explicit ZTraitDef(std::string sId) : ZIdSymbol(std::move(sId), Z_TRAIT_DEF){}
		ZTraitDef(std::string sId, ZLangConstruct c) :  ZIdSymbol(std::move(sId), c) {}

		void setVariantTypeParamList(sp<ZVariantTypeParamList> tps) {
			variantTypeParamList_ = tps;
		}
		sp<ZVariantTypeParamList> getVariantTypeParamList()  {
			return variantTypeParamList_;
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

	class ZClassParamList: public ZSymbol {
	protected:
		vecP<ZClassParam> classParams_;
	public:
		ZClassParamList() : ZSymbol(Z_CLASS_PARAMS) {}
		~ZClassParamList() override = default;
		void addClassParam(sp<ZClassParam> cp) {
			classParams_.push_back(cp);
		}
	};


	class ZBlock: public ZStmtList {
		public:
		ZBlock() : ZStmtList(Z_BLOCK) {}
		ZBlock(ZLangConstruct c) : ZStmtList(Z_BLOCK) {}
		~ZBlock() override = default;
	};

	class ZClassConstr: public ZSymbol {
	protected:
		PVecP<ZClassParam> clsParams_;
	public:
		ZClassConstr() : ZSymbol(Z_CLASS_CONSTR) {}
	};

	class ZTemplateBody : public ZStmtList {
	public:
		ZTemplateBody() : ZStmtList(Z_TEMPLATE_BODY) {}
	};

	class ZClassTemplate: public ZSymbol {
		protected:
		sp<ZTemplateBody> templateBody_;
		sp<ZClassParents> classParents_;
	public:
		ZClassTemplate() : ZSymbol(Z_CLASS_TEMPLATE) {}
		void setTemplateBody(sp<ZTemplateBody> tb) {
			templateBody_ = tb;
		}
		void setClassParents(sp<ZClassParents> cp) {
			classParents_ = cp;
		}
	};

	class ZObjectDef: public ZId, public ZSymbol {
		protected:
		const bool isCase_;
		sp<ZModifiers> modifiers_;
		sp<ZClassTemplate> classTemplate_;
		public:
		explicit ZObjectDef(bool isCase, std::string zId) : isCase_(isCase), ZId(std::move(zId)), ZSymbol(Z_OBJECT_DEF) {}
		void setModifiers(sp<ZModifiers> mods) {
			modifiers_ = mods;
		}
		void setClassTemplate(sp<ZClassTemplate> ct) {
			classTemplate_ = ct;
		}
	};

	class ZClassDef : public ZIdSymbol {
		sp<ZModifiers> modifiers_;
		sp<ZClassDef> parentClass_;
		sp<ZVariantTypeParamList> typeParams_;
		sp<ZClassParamList> classParamList_;
		PVecP<ZTraitDef> traits_;
		// PVecP<ZClassParam> clsParams_;
		PVecP<ZClassConstr> constrs_;
		// PVecP<ZRegFunc> funcs_;
		// PVecP<ZValueDcl> decls_;
		sp<ZClassTemplate> classTemplate_;
	public:
		explicit ZClassDef(std::string zId) : ZIdSymbol(std::move(zId), Z_CLASS_DEF) {}

		void setModifiers(sp<ZModifiers> mods) {
			modifiers_ = mods;
		}
		sp<ZVariantTypeParamList> getVariantTypeParamList() {
			return typeParams_;
		}
		void setVariantTypeParamList(sp<ZVariantTypeParamList> tpl) {
			typeParams_ = tpl;
		}
		sp<ZClassParamList> getClassParamList() {
			return classParamList_;
		}
		void setClassParamList(sp<ZClassParamList> cpl) {
			classParamList_ = cpl;
		}
	};

	class ZProgram: public ZSymbol {
		public:
		ZProgram() : ZSymbol(Z_PROGRAM) {}
	};


	class ZCompileUnit: public ZId, public ZStmtList {
	protected:
		std::string packgName_;

	public:
		explicit ZCompileUnit(std::string zId) : ZId(std::move(zId)), ZStmtList(Z_COMPILATION_UNIT) {
			packgName_ = "_ROOT_PKG_";
		}

		void setPackage(std::string n) {
			packgName_ += "." + n;
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
