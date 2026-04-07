#pragma once

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
	// forward declarations — keeps this header independent of XVisitor.hpp
	class XVisitor;
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
		explicit ZId(std::string qId);
		ZId(const ZId&) = default;
		ZId(ZId&&) = default;
		ZId& operator=(const ZId&) = default;
		ZId& operator=(ZId&&) = default;

		const std::string& strId() const;
		bool operator==(const ZId& other) const;
	};

	class ZSymbol: public std::enable_shared_from_this<ZSymbol> {
	protected:
		const ZLangConstruct langConstruct_;
	public:
		explicit ZSymbol(ZLangConstruct c);
		virtual ~ZSymbol() = default;
		ZLangConstruct getZLangConstruct();
		void accept(std::shared_ptr<XVisitor> visitor);
	};

	class I_ZId {
	protected:
		const ZId zId_;
	public:
		explicit I_ZId(ZId zId);
		explicit I_ZId(std::string s);
		const ZId& getZId() const;
	};

	class ZIdSymbol : public I_ZId, public ZSymbol {
	public:
		ZIdSymbol(std::string sid, ZLangConstruct c);
		~ZIdSymbol() override = default;
	};

	class ZAstNWrap : public ZSymbol {
	private:
		sp<fAstNod> fAstN_;
	public:
		explicit ZAstNWrap(sp<fAstNod> fAstN);
		std::string toString() const;
	};

	class ZScope {
	protected:
		std::unordered_map<std::string, sp<ZSymbol>> symbols_;
	public:
		void addSymbol(const std::string& name, sp<ZSymbol> symbol);
	};

	class ZImport : public ZSymbol {
		std::vector<std::string> imports_;
	public:
		ZImport();
		void addImport(std::string im);
		void addImport(std::vector<std::string> im);
	};

	class ZFunc : public ZSymbol {
	protected:
		PVecP<ZParam> params_;
	public:
		explicit ZFunc(ZLangConstruct c);
		void addParam(sp<ZParam> p);
	};

	class ZTreePostOrderSS {
		PVecP<ZSymbol> postOrderSS_;
	public:
		void push_back(sp<ZSymbol> n);
		std::string toString() const;
		PVecP<ZSymbol> getTreePostOrderSS();
	};

	class ZProdSubTreeN : public ZSymbol {
	protected:
		const sp<ZTreePostOrderSS> postOrderSS_ = ms<ZTreePostOrderSS>();
	public:
		ZProdSubTreeN();
		explicit ZProdSubTreeN(ZLangConstruct c);
		sp<ZTreePostOrderSS> getTreePostOrderSS() const;
	};

	class ZType : public ZSymbol {
	protected:
		sp<ZProdSubTreeN> typeTree_;
	public:
		ZType();
		explicit ZType(ZLangConstruct c);
		void setTypeTree(sp<ZProdSubTreeN> t);
		sp<ZProdSubTreeN> getTypeTree() const;
	};

	class ZTypeList : public ZSymbol {
	protected:
		PVecP<ZType> types_;
	public:
		ZTypeList();
		void addType(sp<ZType> t);
	};

	class ZIf : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> condExpr_;
		sp<ZTreePostOrderSS> bodyExpr_;
		sp<ZTreePostOrderSS> elseBodyExpr_;
	public:
		ZIf();
		void setCondExpr(sp<ZTreePostOrderSS> c);
		void setBody(sp<ZTreePostOrderSS> b);
		void setElseBody(sp<ZTreePostOrderSS> eb);
	};

	class ZModifiers : public ZSymbol {
		std::vector<std::string> modifiers_;
	public:
		ZModifiers();
		void addModifiers(std::string m);
	};

	class ZWhile : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> condExpr_;
		sp<ZTreePostOrderSS> bodyExpr_;
	public:
		ZWhile();
		void setCondExpr(sp<ZTreePostOrderSS> c);
		void setBody(sp<ZTreePostOrderSS> b);
	};

	class ZValueDcl : public ZSymbol {
		sp<ZModifiers> modifiers_;
		sp<ZTreePostOrderSS> type_;
		sp<ZTreePostOrderSS> defaultValueExpr_;
		vecP<ZTreePostOrderSS> names_ = vecP<ZTreePostOrderSS>();
	public:
		ZValueDcl();
		void setDefaultValueExpr(sp<ZTreePostOrderSS> de);
		void setModifiers(sp<ZModifiers> m);
		void setType(sp<ZTreePostOrderSS> t);
		void addName(sp<ZTreePostOrderSS> n);
		vecP<ZTreePostOrderSS> getNames();
	};

	class ZParamType : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> type_;
	public:
		ZParamType();
		explicit ZParamType(ZLangConstruct c);
		~ZParamType() override = default;
		void setType(sp<ZTreePostOrderSS> t);
	};

	class ZTypeParamList : public ZSymbol {
	protected:
		vecP<ZTypeParam> typeParams_;
	public:
		ZTypeParamList();
		~ZTypeParamList() override = default;
		void addTypeParam(sp<ZTypeParam> tp);
		void addTypeParams(vecP<ZTypeParam> tps);
	};

	class ZVariantTypeParamList : public ZSymbol {
	protected:
		vecP<ZVariantTypeParam> typeParams_;
	public:
		ZVariantTypeParamList();
		~ZVariantTypeParamList() override = default;
		void addVariantTypeParam(sp<ZVariantTypeParam> tp);
	};

	class ZTypeParam : public ZIdSymbol {
	protected:
		sp<ZVariantTypeParamList> variantTypeParamList_;
	public:
		explicit ZTypeParam(std::string zId);
		ZTypeParam(std::string zId, ZLangConstruct c);
		~ZTypeParam() override = default;
		void setVariantTypeParamList(sp<ZVariantTypeParamList> vtpList);
		sp<ZVariantTypeParamList> getVariantTypeParamList();
	};

	class ZVariantTypeParam : public ZSymbol {
	protected:
		const fVarianceE variance_;
		sp<ZTypeParam> typeParam_;
	public:
		explicit ZVariantTypeParam(fVarianceE v);
		ZVariantTypeParam(fVarianceE v, ZLangConstruct c);
		~ZVariantTypeParam() override = default;
		void setTypeParam(sp<ZTypeParam> tp);
		sp<ZTypeParam> getTypeParam();
	};

	class ZParam : public ZIdSymbol {
		sp<ZTreePostOrderSS> paramType_;
		sp<ZTreePostOrderSS> defaultExpr_;
	public:
		explicit ZParam(std::string sid);
		ZParam(std::string sid, ZLangConstruct c);
		void setParamType(sp<ZTreePostOrderSS> tp);
		void setDefaultValueExpr(sp<ZTreePostOrderSS> de);
	};

	class ZParamTypeList : public ZSymbol {
	protected:
		vecP<ZParamType> paramTypes_;
	public:
		ZParamTypeList();
		~ZParamTypeList() override = default;
		void addParamType(sp<ZParamType> pt);
	};

	class ZClassConstr : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> args_;
		sp<ZTreePostOrderSS> paramType_;
	public:
		ZClassConstr();
		explicit ZClassConstr(ZLangConstruct c);
		void setParamType(sp<ZTreePostOrderSS> pt);
		void setArgs(sp<ZTreePostOrderSS> args);

	};

	class ZClassParents : public ZSymbol {
		sp<ZClassConstr> classConstr_;
		sp<ZTreePostOrderSS> withType_;
	public:
		ZClassParents();
		~ZClassParents() override = default;
		void setClassConstr(sp<ZClassConstr> cc);
		void setWithType(sp<ZTreePostOrderSS> withType);
	};

	class ZStmtList : public ZScope {
	protected:
		PVecP<ZSymbol> statements_;
	public:
		ZStmtList() = default;
		~ZStmtList() = default;
		void addStmt(sp<ZSymbol> stmt);
		PVecP<ZSymbol> getStmts();
	};

	class ZParamList : public ZSymbol {
	protected:
		PVecP<ZSymbol> params_;
	public:
		ZParamList();
		~ZParamList() = default;
		void addParam(sp<ZParam> p);
	};

	class ZFunSig : public ZIdSymbol {
	protected:
		sp<ZTypeParamList> funTypeParamList_;
		sp<ZParamList> paramList_;
	public:
		explicit ZFunSig(std::string sid);
		void setFunTypeParamList(sp<ZTypeParamList> tps);
		void setParamClauses(sp<ZParamList> p);
	};

	class ZSelfType : public ZIdSymbol {
	protected:
		const std::string name_;
		sp<ZTreePostOrderSS> selfType_;
	public:
		explicit ZSelfType(std::string name);
		ZSelfType(std::string name, ZLangConstruct c);
		void setSelfType(sp<ZTreePostOrderSS> s);
	};

	class ZRegFunc : public ZSymbol {
	protected:
		sp<ZFunSig> funSig_;
		sp<ZTreePostOrderSS> returnType_;
		sp<ZProdSubTreeN> funBodyExpr_;
		sp<ZBlock> funBodyBlock_;
		sp<ZModifiers> modifiers_;
	public:
		ZRegFunc();
		~ZRegFunc() override = default;
		void setModifiers(sp<ZModifiers> m);
		void setFunSig(sp<ZFunSig> sig);
		void setReturnType(sp<ZTreePostOrderSS> rt);
		void setFunBodyExpr(sp<ZProdSubTreeN> e);
		void setFunBodyBlock(sp<ZBlock> b);
		sp<ZFunSig> getFunSig() const;
	};

	class ZClassParam : public ZIdSymbol {
	protected:
		const bool isMutable_;
		sp<ZTreePostOrderSS> paramType_;
		sp<ZTreePostOrderSS> defaultValueExpr_;
	public:
		ZClassParam(std::string sid, bool isMutable);
		ZClassParam(std::string sid, ZLangConstruct c, bool isMutable);
		void setDefaultValueExpr(sp<ZTreePostOrderSS> de);
		void setParamType(sp<ZTreePostOrderSS> pt);
		bool isMutable() const;
	};

	class ZClassParamList : public ZSymbol {
	protected:
		vecP<ZClassParam> classParams_;
	public:
		ZClassParamList();
		~ZClassParamList() override = default;
		void addClassParam(sp<ZClassParam> cp);
	};

	class ZBlock : public ZSymbol, public ZStmtList {
	public:
		ZBlock();
		explicit ZBlock(ZLangConstruct c);
		~ZBlock() override = default;
	};

	class ZTemplateBody : public ZSymbol, public ZStmtList {
	public:
		ZTemplateBody();
		explicit ZTemplateBody(ZLangConstruct c);
		~ZTemplateBody() override = default;
	};

	class ZClassTemplate : public ZSymbol {
	protected:
		sp<ZClassParents> classParents_;
		sp<ZTemplateBody> templateBody_;
	public:
		ZClassTemplate(sp<ZClassParents> parents, sp<ZTemplateBody> tb);
		ZClassTemplate();
		explicit ZClassTemplate(ZLangConstruct c);
		void setClassParents(sp<ZClassParents> cp);
		void setTemplateBody(sp<ZTemplateBody> t);
		sp<ZTemplateBody> getTemplateBody();
	};

	class ZCaseClause : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> guard_;
		sp<ZTreePostOrderSS> pattern_;
		sp<ZBlock> block_;
	public:
		ZCaseClause();
		explicit ZCaseClause(ZLangConstruct c);
		void setGuard(sp<ZTreePostOrderSS> g);
		void setPattern(sp<ZTreePostOrderSS> p);
		void setBlock(sp<ZBlock> b);
	};

	class ZCaseClauses : public ZSymbol {
	protected:
		vecP<ZCaseClause> casesClauses_;
	public:
		ZCaseClauses();
		explicit ZCaseClauses(ZLangConstruct c);
		void addCaseClause(sp<ZCaseClause> c);
	};

	class ZConstrBlock : public ZSymbol, public ZStmtList {
	protected:
		PVecP<ZTreePostOrderSS> argExprs_;
	public:
		ZConstrBlock();
		explicit ZConstrBlock(ZLangConstruct c);
		void addArgExprs(sp<ZTreePostOrderSS> argExpr);
	};

	class ZTraitDef : public ZIdSymbol {
	protected:
		sp<ZModifiers> modifiers_;
		sp<ZVariantTypeParamList> variantTypeParamList_;
		sp<ZTemplateBody> templateBody_;
	public:
		explicit ZTraitDef(std::string sId);
		ZTraitDef(std::string sId, ZLangConstruct c);
		void setVariantTypeParamList(sp<ZVariantTypeParamList> tps);
		sp<ZVariantTypeParamList> getVariantTypeParamList();
		void setTemplateBody(sp<ZTemplateBody> tb);
		sp<ZTemplateBody> getTemplateBody();
		void setModifiers(sp<ZModifiers> mods);
		void accept(std::shared_ptr<XVisitor> visitor);
	};

	class ZObjectDef : public ZIdSymbol {
	protected:
		const bool isCase_;
		sp<ZModifiers> modifiers_;
		sp<ZClassTemplate> classTemplate_;
	public:
		explicit ZObjectDef(bool isCase, std::string zId);
		void setModifiers(sp<ZModifiers> mods);
		void setClassTemplate(sp<ZClassTemplate> ct);
		void accept(std::shared_ptr<XVisitor> visitor);
	};

	class ZAccessModifier : public ZSymbol {
	public:
		ZAccessModifier();
	};

	class ZClassDef : public ZIdSymbol {
		sp<ZModifiers> modifiers_;
		sp<ZClassDef> parentClass_;
		sp<ZVariantTypeParamList> typeParams_;
		sp<ZClassParamList> classParamList_;
		sp<ZClassTemplate> classTemplate_;
		sp<ZAccessModifier> constrAccessModifier_;
	public:
		explicit ZClassDef(std::string zId);
		void setModifiers(sp<ZModifiers> mods);
		sp<ZVariantTypeParamList> getVariantTypeParamList();
		void setVariantTypeParamList(sp<ZVariantTypeParamList> tpl);
		sp<ZClassParamList> getClassParamList();
		void setClassParamList(sp<ZClassParamList> cpl);
		void setClassTemplate(sp<ZClassTemplate> ct);
		void setConstrAccessModifier(sp<ZAccessModifier> acmod);
		void accept(std::shared_ptr<XVisitor> visitor);
	};

	class ZThisFunc : public ZFunc {
	protected:
		sp<ZParamList> paramList_;
		sp<ZConstrBlock> constrBlock_;
	public:
		ZThisFunc();
		void setParamClauses(sp<ZParamList> p);
		void setConstrBlock(sp<ZConstrBlock> cb);
	};

	class ZGenerator : public ZSymbol {
	protected:
		sp<ZTreePostOrderSS> casePattern1_;
		sp<ZTreePostOrderSS> inExpr_;
		PVecP<ZTreePostOrderSS> guards_;
		PVecP<ZTreePostOrderSS> endingPattern1s_;
	public:
		ZGenerator();
		void setCasePattern1(sp<ZTreePostOrderSS> cp);
		void setInExpr(sp<ZTreePostOrderSS> ie);
		void addGuard(sp<ZTreePostOrderSS> g);
		void addEndingPattern1(sp<ZTreePostOrderSS> ep);
		void addEndingExpr(sp<ZTreePostOrderSS> ee);
	};

	class ZFor : public ZSymbol {
		vecP<ZGenerator> generators_;
		sp<ZTreePostOrderSS> yieldExpr_;
	public:
		ZFor();
		void addGenerator(sp<ZGenerator> g);
		void setYieldExpr(sp<ZTreePostOrderSS> y);
	};

	class ZCompileUnit : public ZIdSymbol, public ZStmtList {
	protected:
		std::string packgName_;
	public:
		explicit ZCompileUnit(std::string zId);
		void setPackage(std::string n);
		std::string toString();
	};

	class ZProgram : public ZIdSymbol {
	protected:
		vecP<ZCompileUnit> compileUnits_;
	public:
		explicit ZProgram(std::string progName);
		void addCompileUnit(sp<ZCompileUnit> cu);
		vecP<ZCompileUnit> getCompileUnits();
		std::string toString();
	};

} // namespace zebra::ast::symbol

namespace std {
	template <>
	struct hash<zebra::ast::symbol::ZId> {
		std::size_t operator()(const zebra::ast::symbol::ZId& id) const noexcept {
			return std::hash<std::string>{}(id.strId());
		}
	};
}
