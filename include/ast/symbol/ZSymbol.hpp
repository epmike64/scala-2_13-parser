#pragma once

#include <cassert>

#include "ZLangConstruct.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "ast/node/fAstNod.hpp"
#include "util/fCommon.hpp"
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "util/fUtil.hpp"


namespace zebra::ast::symbol {
	class ZRegFunc;
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
		std::string Id_;
	public:
		explicit ZId(std::string qId) : Id_(std::move(qId)) {}
		ZId(const ZId&) = default;
		ZId(ZId&&) = default;
		ZId& operator=(const ZId&) = default;
		ZId& operator=(ZId&&) = default;

		const std::string& strId() const { return Id_; }

		bool operator==(const ZId& other) const {
			return Id_ == other.Id_;
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

	class ZAstNWrap: public ZSymbol {
	private:
		sp<fAstNod> fAstN_;
	public:
		ZAstNWrap(sp<fAstNod> fAstN) : fAstN_(fAstN), ZSymbol(Z_F_WRAPPER) {}
		std::string toString() const {
			return "ZAstNWrap(" + (fAstN_ ? fAstN_->toString() : "null") + ")";
		}
	};

	class ZScope {
	protected:
		std::unordered_map<std::string, sp<ZSymbol>> symbols_;
	public:
		void addSymbol(const std::string& name, sp<ZSymbol> symbol) {
			zaccert(symbol != nullptr, "Cannot add null symbol to scope");
			if (symbols_.find(name) != symbols_.end()) {
				throw std::runtime_error("Symbol with name '" + name + "' already exists in scope");
			}
			symbols_[name] = symbol;
		}
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
		PVecP<ZSymbol> postOrderSS_;
	public:
		void push_back(sp<ZSymbol> n) {
			zaccert(n != nullptr, "Cannot push null symbol to post-order symbol stack");
			if (postOrderSS_ == nullptr) {
				postOrderSS_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
			}
			postOrderSS_->push_back(n);
		}
		std::string toString() const{
			std::stringstream out;
			out << "PostOrderSS: [";
			for (const auto& sym : *postOrderSS_) {
				out << sym  << ", ";
			}
			out << "]";
			return out.str();
		}

		PVecP<ZSymbol> getTreePostOrderSS() {
			return postOrderSS_;
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

	class ZType : public ZSymbol {
	protected:
		sp<ZProdSubTreeN> typeTree_;
	public:
		ZType(): ZSymbol(Z_TYPE) {}
		explicit ZType(ZLangConstruct c) : ZSymbol(c) {}
		void setTypeTree(sp<ZProdSubTreeN> t) {
			typeTree_ = t;
		}
		sp<ZProdSubTreeN> getTypeTree() const {
			return typeTree_;
		}
	};

	class ZTypeList: public ZSymbol {
	protected:
		PVecP<ZType> types_;
	public:
		ZTypeList() : ZSymbol(Z_TYPE_LIST) {}
		void addType(sp<ZType> t) {
			if (types_ == nullptr) {
				types_ = ms<std::vector<std::shared_ptr<ZType>>>();
			}
			types_->push_back(t);
		}
	};

	class ZIf: public ZSymbol {
	protected:
		sp<ZTreePostOrderSS>  condExpr_;
		sp<ZTreePostOrderSS>  bodyExpr_;
		sp<ZTreePostOrderSS>  elseBodyExpr_;
	public:
		ZIf() : ZSymbol(Z_IF) {}
		void setCondExpr(sp<ZTreePostOrderSS> c) {
			condExpr_ = c;
		}
		void setBody(sp<ZTreePostOrderSS> b) {
			bodyExpr_ = b;
		}
		void setElseBody(sp<ZTreePostOrderSS> eb) {
			elseBodyExpr_ = eb;
		}
	};

	class ZModifiers: public ZSymbol {
		std::vector<std::string> modifiers_;
		public:
		ZModifiers() : ZSymbol(Z_MODIFIERS) {}
		void addModifiers(std::string m) {
			modifiers_.push_back(std::move(m));
		}
	};

	class ZWhile: public ZSymbol {
	protected:
		sp<ZTreePostOrderSS>  condExpr_;
		sp<ZTreePostOrderSS>  bodyExpr_;
	public:
		ZWhile() : ZSymbol(Z_WHILE) {}
		void setCondExpr(sp<ZTreePostOrderSS> c) {
			condExpr_ = c;
		}
		void setBody(sp<ZTreePostOrderSS> b) {
			bodyExpr_ = b;
		}
	};

	class ZValueDcl: public ZSymbol {
		sp<ZModifiers> modifiers_;
		sp<ZTreePostOrderSS> type_;

		sp<ZTreePostOrderSS> defaultValueExpr_;
		vecP<ZTreePostOrderSS> names_  = vecP<ZTreePostOrderSS>();
		public:
		ZValueDcl() : ZSymbol(Z_VALUE_DCL) {}

		void setDefaultValueExpr(sp<ZTreePostOrderSS> de) {
			defaultValueExpr_ = de;
		}
		void setModifiers(sp<ZModifiers> m) {
			modifiers_ = m;
		}
		void setType(sp<ZTreePostOrderSS> t) {
			type_ = t;
		}
		void addName(sp<ZTreePostOrderSS> n) {
			names_.push_back(n);
		}

		vecP<ZTreePostOrderSS> getNames() {
			return names_;
		}
	};

	class ZParamType: public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> type_;
		public:
		ZParamType() : ZSymbol(Z_PARAM_TYPE) {}
		explicit ZParamType(ZLangConstruct c) : ZSymbol(c) {}
		~ZParamType() override = default;
		void setType(sp<ZTreePostOrderSS> t) {
			type_ = t;
		}
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


	class ZParam : public ZIdSymbol {
		sp<ZTreePostOrderSS> paramType_;
		sp<ZTreePostOrderSS> defaultExpr_;
		public:
		explicit ZParam(std::string sid): ZIdSymbol(sid, Z_PARAM) {}
		ZParam(std::string sid, ZLangConstruct c) : ZIdSymbol(sid, c) {}

		void setParamType(sp<ZTreePostOrderSS> tp) {
			paramType_ = tp;
		}
		void setDefaultValueExpr(sp<ZTreePostOrderSS> de) {
			defaultExpr_ = de;
		}
	};

	class ZParamTypeList: public ZSymbol {
		protected:
		vecP<ZParamType> paramTypes_;
		public:
		ZParamTypeList() : ZSymbol(Z_TYPE_PARAMS) {}
		~ZParamTypeList() override = default;
		void addParamType(sp<ZParamType> pt) {
			paramTypes_.push_back(pt);
		}
	};

	class ZClassConstr: public ZSymbol {
		protected:
		sp<ZTreePostOrderSS> args_;
		sp<ZTreePostOrderSS> paramType_;
	public:
		ZClassConstr() : ZSymbol(Z_CLASS_CONSTR) {}
		ZClassConstr(ZLangConstruct c) : ZSymbol(c) {}

		void setParamType(sp<ZTreePostOrderSS> pt) {
			paramType_ = pt;
		}
		void setArgs(sp<ZTreePostOrderSS> args) {
			args_ = args;
		}
	};

	class ZClassParents: public ZSymbol {
		sp<ZClassConstr> classConstr_;
		sp<ZTreePostOrderSS> withType_;
	public:
		ZClassParents() : ZSymbol(Z_CLASS_PARENTS) {}
		~ZClassParents() override = default;
		void setClassConstr(sp<ZClassConstr> cc) {
			classConstr_ = cc;
		}
		void setWithType(sp<ZTreePostOrderSS> withType) {
			withType_ = withType;
		}
	};

	class ZStmtList: public ZScope  {
	protected:
		PVecP<ZSymbol> statements_;
	public:
		ZStmtList() = default;
		~ZStmtList() = default;

		void addStmt(sp<ZSymbol> stmt); // defined after ZRegFunc is fully declared

		PVecP<ZSymbol> getStmts() {
			return statements_;
		}
	};

	class ZParamList: public ZSymbol {
		protected:
		PVecP<ZSymbol> params_;
		public: ZParamList() : ZSymbol(Z_PARAM_LIST) {}
		~ZParamList() = default;
		void addParam(sp<ZParam> p) {
			if (params_ == nullptr) {
				params_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
			}
			params_->push_back(p);
		}
	};

	class ZFunSig: public ZIdSymbol {
	protected:
		sp<ZTypeParamList> funTypeParamList_;
		sp<ZParamList> paramList_;
	public:
		explicit ZFunSig(std::string sid) : ZIdSymbol(std::move(sid), Z_FUN_SIG) {}
		void setFunTypeParamList(sp<ZTypeParamList> tps) {
			funTypeParamList_ = tps;
		}
		void setParamClauses(sp<ZParamList> p) {
			paramList_ = p;
		}
	};

	class ZRegFunc: public ZSymbol {
	protected:
		sp<ZFunSig> funSig_;
		sp<ZTreePostOrderSS> returnType_;
		sp<ZProdSubTreeN> funBodyExpr_;
		sp<ZBlock> funBodyBlock_;
		sp<ZModifiers> modifiers_;
		public:
		ZRegFunc() : ZSymbol(Z_REG_FUNC_DEF) {}
		~ZRegFunc() override = default;

		void setModifiers(sp<ZModifiers> m) {
			modifiers_ = m;
		}

		void setFunSig(sp<ZFunSig> sig) {
			funSig_ = sig;
		}

		void setReturnType(sp<ZTreePostOrderSS> rt) {
			returnType_ = rt;
		}

		void setFunBodyExpr(sp<ZProdSubTreeN> e) {
			funBodyExpr_ = e;
		}
		void setFunBodyBlock(sp<ZBlock> b) {
			funBodyBlock_ = b;
		}

		sp<ZFunSig> getFunSig() const {
			return funSig_;
		}
	};

	// ZRegFunc is now fully defined — provide the body of ZStmtList::addStmt here
	// to break the circular dependency (ZBlock inherits ZStmtList, ZRegFunc holds sp<ZBlock>).
	inline void ZStmtList::addStmt(sp<ZSymbol> stmt) {
		assert(stmt != nullptr);
		if (statements_ == nullptr) {
			statements_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
		}
		statements_->push_back(stmt);
		switch (stmt->getZLangConstruct()) {
			case Z_CLASS_DEF: case Z_TRAIT_DEF: case Z_OBJECT_DEF:  {
				addSymbol(std::dynamic_pointer_cast<ZIdSymbol>(stmt)->getZId().strId(), stmt);
				break;
			}
			case Z_REG_FUNC_DEF: {
				// ZFunSig inherits its id via I_ZId::getZId(), so use getZId().strId()
				addSymbol(std::dynamic_pointer_cast<ZRegFunc>(stmt)->getFunSig()->getZId().strId(), stmt);
				break;
			}
			case Z_VALUE_DCL: {
				sp<ZValueDcl> v = std::dynamic_pointer_cast<ZValueDcl>(stmt);
				std::string name;
				for (const auto& nameSS : v->getNames()) {
					PVecP<ZSymbol> vp = nameSS->getTreePostOrderSS();
					if (vp != nullptr) {
						sp<ZSymbol> first = vp->front();
						if (first != nullptr && first->getZLangConstruct() == Z_F_WRAPPER) {
							sp<ZAstNWrap> astNWrap = std::dynamic_pointer_cast<ZAstNWrap>(first);
							if (astNWrap != nullptr && astNWrap->getZLangConstruct() == Z_F_WRAPPER) {
								std::string varName = astNWrap->toString(); // Assuming toString returns the variable name
								// addSymbol(varName, stmt);
								name += varName;
							} else {
								throw std::runtime_error("Expected ZAstNWrap in post-order symbol stack for value declaration");
							}
						} else {
							throw std::runtime_error("Expected first symbol in post-order symbol stack to be a ZAstNWrap for value declaration");
						}
					}
					if (!name.empty()) {
						addSymbol(name, stmt);
					}
				}
				break;
			}
			default:
				break;
		}
	}

	class ZClassParam: public ZIdSymbol{
	protected:
		const bool isMutable_;
		sp<ZTreePostOrderSS> paramType_;
		sp<ZTreePostOrderSS> defaultValueExpr_;
	public:
		ZClassParam(std::string sid, bool isMutable) : ZIdSymbol(std::move(sid), Z_CLASS_PARAM), isMutable_(isMutable) {}
		ZClassParam(std::string sid, ZLangConstruct c, bool isMutable) : ZIdSymbol(std::move(sid), c), isMutable_(isMutable) {}

		void setDefaultValueExpr(sp<ZTreePostOrderSS> de) {
			defaultValueExpr_ = de;
		}

		void setParamType(sp<ZTreePostOrderSS> pt) {
			paramType_ = pt;
		}

		bool isMutable() const {
			return isMutable_;
		}
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


	class ZBlock: public ZSymbol, public ZStmtList{
		public:
		ZBlock() : ZSymbol(Z_BLOCK) {}
		ZBlock(ZLangConstruct c) : ZSymbol(Z_BLOCK) {}
		~ZBlock() override = default;
	};

	class ZTemplateBody : public ZSymbol, public ZStmtList {
	public:
		ZTemplateBody() : ZSymbol(Z_TEMPLATE_BODY) {}
		ZTemplateBody(ZLangConstruct c) : ZSymbol(c) {}
		~ZTemplateBody() override = default;
	};

	class ZClassTemplate:  public ZSymbol  {
		protected:
		sp<ZClassParents> classParents_;
		sp<ZTemplateBody> templateBody_;
	public:
		ZClassTemplate(sp<ZClassParents> parents, sp<ZTemplateBody> tb) : ZSymbol(Z_CLASS_TEMPLATE), classParents_(parents), templateBody_(tb) {}
		ZClassTemplate() : ZSymbol(Z_CLASS_TEMPLATE) {}
		ZClassTemplate(ZLangConstruct c) : ZSymbol(Z_CLASS_TEMPLATE) {}

		void setClassParents(sp<ZClassParents> cp) {
			classParents_ = cp;
		}
		void setTemplateBody(sp<ZTemplateBody> t) {
			templateBody_ = t;
		}
		sp<ZTemplateBody> getTemplateBody() {
			return templateBody_;
		}
	};

	class ZCaseClause: public ZSymbol {
		protected:
		sp<ZTreePostOrderSS> guard_;
		sp<ZTreePostOrderSS> pattern_;
		sp<ZBlock> block_;
		public:
		ZCaseClause() : ZSymbol(Z_CASE_CLAUSE) {}
		ZCaseClause(ZLangConstruct c) : ZSymbol(c) {}
		void setGuard(sp<ZTreePostOrderSS> g) {
			guard_ = g;
		}
		void setPattern(sp<ZTreePostOrderSS> p) {
			pattern_ = p;
		}
		void setBlock(sp<ZBlock> b) {
			block_ = b;
		}
	};

	class ZCaseClauses: public ZSymbol {
		protected:
		vecP<ZCaseClause> casesClauses_;
		public:
		ZCaseClauses() : ZSymbol(Z_CASE_CLAUSES) {}
		ZCaseClauses(ZLangConstruct c) : ZSymbol(c) {}
		void addCaseClause(sp<ZCaseClause> c) {
			casesClauses_.push_back(c);
		}
	};

	class ZConstrBlock: public ZSymbol, public ZStmtList {
		protected:
		PVecP<ZTreePostOrderSS> argExprs_;

		public:
		ZConstrBlock() : ZSymbol(Z_CONSTR_BLOCK) {}
		ZConstrBlock(ZLangConstruct c) : ZSymbol(c) {}
		void addArgExprs(sp<ZTreePostOrderSS> argExpr) {
			if (argExprs_ == nullptr) {
				argExprs_ = ms<std::vector<std::shared_ptr<ZTreePostOrderSS>>>();
			}
			argExprs_->push_back(argExpr);
		}
	};

	class ZTraitDef: public ZIdSymbol{
	protected:
		sp<ZModifiers> modifiers_;
		sp<ZVariantTypeParamList> variantTypeParamList_;
		sp<ZTemplateBody> templateBody_;
	public:
		explicit ZTraitDef(std::string sId) : ZIdSymbol(std::move(sId), Z_TRAIT_DEF){}
		ZTraitDef(std::string sId, ZLangConstruct c) :  ZIdSymbol(std::move(sId), c) {}

		void setVariantTypeParamList(sp<ZVariantTypeParamList> tps) {
			variantTypeParamList_ = tps;
		}
		sp<ZVariantTypeParamList> getVariantTypeParamList()  {
			return variantTypeParamList_;
		}
		void setTemplateBody(sp<ZTemplateBody> tb) {
			templateBody_ = tb;
		}
		sp<ZTemplateBody> getTemplateBody() {
			return templateBody_;
		}
		void setModifiers(sp<ZModifiers> mods) {
			modifiers_ = mods;
		}

	};

	class ZObjectDef: public ZIdSymbol {
		protected:
		const bool isCase_;
		sp<ZModifiers> modifiers_;
		sp<ZClassTemplate> classTemplate_;
		public:
		explicit ZObjectDef(bool isCase, std::string zId) : isCase_(isCase), ZIdSymbol(std::move(zId), Z_OBJECT_DEF) {}
		void setModifiers(sp<ZModifiers> mods) {
			modifiers_ = mods;
		}
		void setClassTemplate(sp<ZClassTemplate> ct) {
			classTemplate_ = ct;
		}
	};

	class ZAccessModifier: public ZSymbol {
	public:
		ZAccessModifier() : ZSymbol(Z_ACCESS_MODIFIER) {}
	};

	class ZClassDef : public ZIdSymbol{
		sp<ZModifiers> modifiers_;
		sp<ZClassDef> parentClass_;
		sp<ZVariantTypeParamList> typeParams_;
		sp<ZClassParamList> classParamList_;
		sp<ZClassTemplate> classTemplate_;
		sp<ZAccessModifier> constrAccessModifier_;
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
		void setClassTemplate(sp<ZClassTemplate> ct) {
			classTemplate_ = ct;
		}
		void setConstrAccessModifier(sp<ZAccessModifier> acmod) {
			constrAccessModifier_ = acmod;
		}
	};




	class ZCompileUnit: public ZIdSymbol, public ZStmtList {
	protected:
		std::string packgName_;

	public:
		explicit ZCompileUnit(std::string zId) : ZIdSymbol(std::move(zId),Z_COMPILATION_UNIT)  {
			packgName_ = "_ROOT_PKG_";
		}

		void setPackage(std::string n) {
			packgName_ += "." + n;
		}

		std::string toString() {
			return "ZCompileUnit(" + getZId().strId() + ", Package: " + packgName_ + ", Stmts: " + std::to_string(statements_ ? statements_->size() : 0) + ")";
		}
	};

	class ZProgram: public ZIdSymbol {
	protected:
		vecP<ZCompileUnit> compileUnits_;
	public:
		ZProgram(std::string progName) : ZIdSymbol(std::move(progName), Z_PROGRAM) {}

		void addCompileUnit(sp<ZCompileUnit> cu) {
			compileUnits_.push_back(cu);
		}

		vecP<ZCompileUnit> getCompileUnits() {
			return compileUnits_;
		}

		std::string toString() {
			return "ZProgram(" + getZId().strId() + ", CompileUnits: " + std::to_string(compileUnits_.size()) + ")";
		}
	};

}

namespace std {
	template <>
	struct hash<zebra::ast::symbol::ZId> {
		std::size_t operator()(const zebra::ast::symbol::ZId& id) const noexcept {
			return std::hash<std::string>{}(id.strId());
		}
	};
}
