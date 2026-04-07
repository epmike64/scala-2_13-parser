#include "ast/symbol/ZSymbol.hpp"

#include <cassert>

#include "ast/symbol/XVisitor.hpp"
#include "util/fUtil.hpp"
#include "ast/symbol/XEnclSc.hpp"

namespace zebra::ast::symbol {

	// ── ZId ──────────────────────────────────────────────────────────────
	ZId::ZId(std::string qId) : Id_(std::move(qId)) {}

	const std::string& ZId::strId() const { return Id_; }

	bool ZId::operator==(const ZId& other) const { return Id_ == other.Id_; }

	// ── ZSymbol ───────────────────────────────────────────────────────────
	ZSymbol::ZSymbol(ZLangConstruct c) : langConstruct_(c) {}

	ZLangConstruct ZSymbol::getZLangConstruct() { return langConstruct_; }

	// ── I_ZId ─────────────────────────────────────────────────────────────
	I_ZId::I_ZId(ZId zId) : zId_(std::move(zId)) {}

	I_ZId::I_ZId(std::string s) : zId_(ZId(std::move(s))) {}

	const ZId& I_ZId::getZId() const { return zId_; }

	// ── ZIdSymbol ─────────────────────────────────────────────────────────
	ZIdSymbol::ZIdSymbol(std::string sid, ZLangConstruct c)
		: I_ZId(std::move(sid)), ZSymbol(c) {}

	// ── ZAstNWrap ─────────────────────────────────────────────────────────
	ZAstNWrap::ZAstNWrap(sp<fAstNod> fAstN) : fAstN_(fAstN), ZSymbol(Z_F_WRAPPER) {}

	std::string ZAstNWrap::toString() const {
		return "ZAstNWrap(" + (fAstN_ ? fAstN_->toString() : "null") + ")";
	}

	// ── ZScope ────────────────────────────────────────────────────────────
	void ZScope::addSymbol(const std::string& name, sp<ZSymbol> symbol) {
		zaccert(symbol != nullptr, "Cannot add null symbol to scope");
		if (symbols_.find(name) != symbols_.end()) {
			throw std::runtime_error("Symbol with name '" + name + "' already exists in scope");
		}
		symbols_[name] = symbol;
	}

	// ── ZImport ───────────────────────────────────────────────────────────
	ZImport::ZImport() : ZSymbol(Z_IMPORT) {}

	void ZImport::addImport(std::string im) {
		imports_.push_back(std::move(im));
	}

	void ZImport::addImport(std::vector<std::string> im) {
		imports_.insert(imports_.end(),
			std::make_move_iterator(im.begin()),
			std::make_move_iterator(im.end()));
	}

	// ── ZFunc ─────────────────────────────────────────────────────────────
	ZFunc::ZFunc(ZLangConstruct c) : ZSymbol(c) {}

	void ZFunc::addParam(sp<ZParam> p) {
		if (params_ == nullptr) {
			params_ = ms<std::vector<std::shared_ptr<ZParam>>>();
		}
		params_->push_back(p);
	}

	// ── ZTreePostOrderSS ──────────────────────────────────────────────────
	void ZTreePostOrderSS::push_back(sp<ZSymbol> n) {
		zaccert(n != nullptr, "Cannot push null symbol to post-order symbol stack");
		if (postOrderSS_ == nullptr) {
			postOrderSS_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
		}
		postOrderSS_->push_back(n);
	}

	std::string ZTreePostOrderSS::toString() const {
		std::stringstream out;
		out << "PostOrderSS: [";
		for (const auto& sym : *postOrderSS_) {
			out << sym << ", ";
		}
		out << "]";
		return out.str();
	}

	PVecP<ZSymbol> ZTreePostOrderSS::getTreePostOrderSS() { return postOrderSS_; }

	// ── ZProdSubTreeN ─────────────────────────────────────────────────────
	ZProdSubTreeN::ZProdSubTreeN() : ZSymbol(Z_PROD_SUB_TREE_NOD) {}

	ZProdSubTreeN::ZProdSubTreeN(ZLangConstruct c) : ZSymbol(c) {}

	sp<ZTreePostOrderSS> ZProdSubTreeN::getTreePostOrderSS() const { return postOrderSS_; }

	// ── ZType ─────────────────────────────────────────────────────────────
	ZType::ZType() : ZSymbol(Z_TYPE) {}

	ZType::ZType(ZLangConstruct c) : ZSymbol(c) {}

	void ZType::setTypeTree(sp<ZProdSubTreeN> t) { typeTree_ = t; }

	sp<ZProdSubTreeN> ZType::getTypeTree() const { return typeTree_; }

	// ── ZTypeList ─────────────────────────────────────────────────────────
	ZTypeList::ZTypeList() : ZSymbol(Z_TYPE_LIST) {}

	void ZTypeList::addType(sp<ZType> t) {
		if (types_ == nullptr) {
			types_ = ms<std::vector<std::shared_ptr<ZType>>>();
		}
		types_->push_back(t);
	}

	// ── ZIf ───────────────────────────────────────────────────────────────
	ZIf::ZIf() : ZSymbol(Z_IF) {}

	void ZIf::setCondExpr(sp<ZTreePostOrderSS> c) { condExpr_ = c; }

	void ZIf::setBody(sp<ZTreePostOrderSS> b) { bodyExpr_ = b; }

	void ZIf::setElseBody(sp<ZTreePostOrderSS> eb) { elseBodyExpr_ = eb; }

	// ── ZModifiers ────────────────────────────────────────────────────────
	ZModifiers::ZModifiers() : ZSymbol(Z_MODIFIERS) {}

	void ZModifiers::addModifiers(std::string m) { modifiers_.push_back(std::move(m)); }

	// ── ZWhile ────────────────────────────────────────────────────────────
	ZWhile::ZWhile() : ZSymbol(Z_WHILE) {}

	void ZWhile::setCondExpr(sp<ZTreePostOrderSS> c) { condExpr_ = c; }

	void ZWhile::setBody(sp<ZTreePostOrderSS> b) { bodyExpr_ = b; }

	// ── ZValueDcl ─────────────────────────────────────────────────────────
	ZValueDcl::ZValueDcl() : ZSymbol(Z_VALUE_DCL) {}

	void ZValueDcl::setDefaultValueExpr(sp<ZTreePostOrderSS> de) { defaultValueExpr_ = de; }

	void ZValueDcl::setModifiers(sp<ZModifiers> m) { modifiers_ = m; }

	void ZValueDcl::setType(sp<ZTreePostOrderSS> t) { type_ = t; }

	void ZValueDcl::addName(sp<ZTreePostOrderSS> n) { names_.push_back(n); }

	vecP<ZTreePostOrderSS> ZValueDcl::getNames() { return names_; }

	// ── ZParamType ────────────────────────────────────────────────────────
	ZParamType::ZParamType() : ZSymbol(Z_PARAM_TYPE) {}

	ZParamType::ZParamType(ZLangConstruct c) : ZSymbol(c) {}

	void ZParamType::setType(sp<ZTreePostOrderSS> t) { type_ = t; }

	// ── ZTypeParamList ────────────────────────────────────────────────────
	ZTypeParamList::ZTypeParamList() : ZSymbol(Z_TYPE_PARAMS) {}

	void ZTypeParamList::addTypeParam(sp<ZTypeParam> tp) { typeParams_.push_back(tp); }

	void ZTypeParamList::addTypeParams(vecP<ZTypeParam> tps) {
		typeParams_.insert(typeParams_.end(), tps.begin(), tps.end());
	}

	// ── ZVariantTypeParamList ─────────────────────────────────────────────
	ZVariantTypeParamList::ZVariantTypeParamList() : ZSymbol(Z_VARIANT_TYPE_PARAMS) {}

	void ZVariantTypeParamList::addVariantTypeParam(sp<ZVariantTypeParam> tp) {
		typeParams_.push_back(tp);
	}

	// ── ZTypeParam ────────────────────────────────────────────────────────
	ZTypeParam::ZTypeParam(std::string zId) : ZIdSymbol(std::move(zId), Z_TYPE_PARAM) {}

	ZTypeParam::ZTypeParam(std::string zId, ZLangConstruct c) : ZIdSymbol(std::move(zId), c) {}

	void ZTypeParam::setVariantTypeParamList(sp<ZVariantTypeParamList> vtpList) {
		variantTypeParamList_ = vtpList;
	}

	sp<ZVariantTypeParamList> ZTypeParam::getVariantTypeParamList() {
		return variantTypeParamList_;
	}

	// ── ZVariantTypeParam ─────────────────────────────────────────────────
	ZVariantTypeParam::ZVariantTypeParam(fVarianceE v)
		: ZSymbol(Z_VARIANT_TYPE_PARAM), variance_(v) {}

	ZVariantTypeParam::ZVariantTypeParam(fVarianceE v, ZLangConstruct c)
		: ZSymbol(c), variance_(v) {}

	void ZVariantTypeParam::setTypeParam(sp<ZTypeParam> tp) { typeParam_ = tp; }

	sp<ZTypeParam> ZVariantTypeParam::getTypeParam() { return typeParam_; }

	// ── ZParam ────────────────────────────────────────────────────────────
	ZParam::ZParam(std::string sid) : ZIdSymbol(sid, Z_PARAM) {}

	ZParam::ZParam(std::string sid, ZLangConstruct c) : ZIdSymbol(sid, c) {}

	void ZParam::setParamType(sp<ZTreePostOrderSS> tp) { paramType_ = tp; }

	void ZParam::setDefaultValueExpr(sp<ZTreePostOrderSS> de) { defaultExpr_ = de; }

	// ── ZParamTypeList ────────────────────────────────────────────────────
	ZParamTypeList::ZParamTypeList() : ZSymbol(Z_TYPE_PARAMS) {}

	void ZParamTypeList::addParamType(sp<ZParamType> pt) { paramTypes_.push_back(pt); }

	// ── ZClassConstr ──────────────────────────────────────────────────────
	ZClassConstr::ZClassConstr() : ZSymbol(Z_CLASS_CONSTR) {}

	ZClassConstr::ZClassConstr(ZLangConstruct c) : ZSymbol(c) {}

	void ZClassConstr::setParamType(sp<ZTreePostOrderSS> pt) { paramType_ = pt; }

	void ZClassConstr::setArgs(sp<ZTreePostOrderSS> args) { args_ = args; }

	// ── ZClassParents ─────────────────────────────────────────────────────
	ZClassParents::ZClassParents() : ZSymbol(Z_CLASS_PARENTS) {}

	void ZClassParents::setClassConstr(sp<ZClassConstr> cc) { classConstr_ = cc; }

	void ZClassParents::setWithType(sp<ZTreePostOrderSS> withType) { withType_ = withType; }

	// ── ZStmtList ─────────────────────────────────────────────────────────
	PVecP<ZSymbol> ZStmtList::getStmts() { return statements_; }

	void ZStmtList::addStmt(sp<ZSymbol> stmt) {
		assert(stmt != nullptr);
		if (statements_ == nullptr) {
			statements_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
		}
		statements_->push_back(stmt);
		switch (stmt->getZLangConstruct()) {
			case Z_CLASS_DEF: case Z_TRAIT_DEF: case Z_OBJECT_DEF: {
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
								std::string varName = astNWrap->toString();
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

	// ── ZParamList ────────────────────────────────────────────────────────
	ZParamList::ZParamList() : ZSymbol(Z_PARAM_LIST) {}

	void ZParamList::addParam(sp<ZParam> p) {
		if (params_ == nullptr) {
			params_ = ms<std::vector<std::shared_ptr<ZSymbol>>>();
		}
		params_->push_back(p);
	}

	// ── ZFunSig ───────────────────────────────────────────────────────────
	ZFunSig::ZFunSig(std::string sid) : ZIdSymbol(std::move(sid), Z_FUN_SIG) {}

	void ZFunSig::setFunTypeParamList(sp<ZTypeParamList> tps) { funTypeParamList_ = tps; }

	void ZFunSig::setParamClauses(sp<ZParamList> p) { paramList_ = p; }

	// ── ZSelfType ─────────────────────────────────────────────────────────
	ZSelfType::ZSelfType(std::string name)
		: ZIdSymbol(name, Z_SELF_TYPE), name_(std::move(name)) {}

	ZSelfType::ZSelfType(std::string name, ZLangConstruct c)
		: ZIdSymbol(name, c), name_(std::move(name)) {}

	void ZSelfType::setSelfType(sp<ZTreePostOrderSS> s) { selfType_ = s; }

	// ── ZRegFunc ──────────────────────────────────────────────────────────
	ZRegFunc::ZRegFunc() : ZSymbol(Z_REG_FUNC_DEF) {}

	void ZRegFunc::setModifiers(sp<ZModifiers> m) { modifiers_ = m; }

	void ZRegFunc::setFunSig(sp<ZFunSig> sig) { funSig_ = sig; }

	void ZRegFunc::setReturnType(sp<ZTreePostOrderSS> rt) { returnType_ = rt; }

	void ZRegFunc::setFunBodyExpr(sp<ZProdSubTreeN> e) { funBodyExpr_ = e; }

	void ZRegFunc::setFunBodyBlock(sp<ZBlock> b) { funBodyBlock_ = b; }

	sp<ZFunSig> ZRegFunc::getFunSig() const { return funSig_; }

	// ── ZClassParam ───────────────────────────────────────────────────────
	ZClassParam::ZClassParam(std::string sid, bool isMutable)
		: ZIdSymbol(std::move(sid), Z_CLASS_PARAM), isMutable_(isMutable) {}

	ZClassParam::ZClassParam(std::string sid, ZLangConstruct c, bool isMutable)
		: ZIdSymbol(std::move(sid), c), isMutable_(isMutable) {}

	void ZClassParam::setDefaultValueExpr(sp<ZTreePostOrderSS> de) { defaultValueExpr_ = de; }

	void ZClassParam::setParamType(sp<ZTreePostOrderSS> pt) { paramType_ = pt; }

	bool ZClassParam::isMutable() const { return isMutable_; }

	// ── ZClassParamList ───────────────────────────────────────────────────
	ZClassParamList::ZClassParamList() : ZSymbol(Z_CLASS_PARAMS) {}

	void ZClassParamList::addClassParam(sp<ZClassParam> cp) { classParams_.push_back(cp); }

	// ── ZBlock ────────────────────────────────────────────────────────────
	ZBlock::ZBlock() : ZSymbol(Z_BLOCK) {}

	ZBlock::ZBlock(ZLangConstruct c) : ZSymbol(Z_BLOCK) {}

	// ── ZTemplateBody ─────────────────────────────────────────────────────
	ZTemplateBody::ZTemplateBody() : ZSymbol(Z_TEMPLATE_BODY) {}

	ZTemplateBody::ZTemplateBody(ZLangConstruct c) : ZSymbol(c) {}

	// ── ZClassTemplate ────────────────────────────────────────────────────
	ZClassTemplate::ZClassTemplate(sp<ZClassParents> parents, sp<ZTemplateBody> tb)
		: ZSymbol(Z_CLASS_TEMPLATE), classParents_(parents), templateBody_(tb) {}

	ZClassTemplate::ZClassTemplate() : ZSymbol(Z_CLASS_TEMPLATE) {}

	ZClassTemplate::ZClassTemplate(ZLangConstruct c) : ZSymbol(Z_CLASS_TEMPLATE) {}

	void ZClassTemplate::setClassParents(sp<ZClassParents> cp) { classParents_ = cp; }

	void ZClassTemplate::setTemplateBody(sp<ZTemplateBody> t) { templateBody_ = t; }

	sp<ZTemplateBody> ZClassTemplate::getTemplateBody() { return templateBody_; }

	// ── ZCaseClause ───────────────────────────────────────────────────────
	ZCaseClause::ZCaseClause() : ZSymbol(Z_CASE_CLAUSE) {}

	ZCaseClause::ZCaseClause(ZLangConstruct c) : ZSymbol(c) {}

	void ZCaseClause::setGuard(sp<ZTreePostOrderSS> g) { guard_ = g; }

	void ZCaseClause::setPattern(sp<ZTreePostOrderSS> p) { pattern_ = p; }

	void ZCaseClause::setBlock(sp<ZBlock> b) { block_ = b; }

	// ── ZCaseClauses ──────────────────────────────────────────────────────
	ZCaseClauses::ZCaseClauses() : ZSymbol(Z_CASE_CLAUSES) {}

	ZCaseClauses::ZCaseClauses(ZLangConstruct c) : ZSymbol(c) {}

	void ZCaseClauses::addCaseClause(sp<ZCaseClause> c) { casesClauses_.push_back(c); }

	// ── ZConstrBlock ──────────────────────────────────────────────────────
	ZConstrBlock::ZConstrBlock() : ZSymbol(Z_CONSTR_BLOCK) {}

	ZConstrBlock::ZConstrBlock(ZLangConstruct c) : ZSymbol(c) {}

	void ZConstrBlock::addArgExprs(sp<ZTreePostOrderSS> argExpr) {
		if (argExprs_ == nullptr) {
			argExprs_ = ms<std::vector<std::shared_ptr<ZTreePostOrderSS>>>();
		}
		argExprs_->push_back(argExpr);
	}

	// ── ZTraitDef ─────────────────────────────────────────────────────────
	ZTraitDef::ZTraitDef(std::string sId) : ZIdSymbol(std::move(sId), Z_TRAIT_DEF) {}

	ZTraitDef::ZTraitDef(std::string sId, ZLangConstruct c) : ZIdSymbol(std::move(sId), c) {}

	void ZTraitDef::setVariantTypeParamList(sp<ZVariantTypeParamList> tps) {
		variantTypeParamList_ = tps;
	}

	sp<ZVariantTypeParamList> ZTraitDef::getVariantTypeParamList() {
		return variantTypeParamList_;
	}

	void ZTraitDef::setTemplateBody(sp<ZTemplateBody> tb) { templateBody_ = tb; }

	sp<ZTemplateBody> ZTraitDef::getTemplateBody() { return templateBody_; }

	void ZTraitDef::setModifiers(sp<ZModifiers> mods) { modifiers_ = mods; }

	// ── ZObjectDef ────────────────────────────────────────────────────────
	ZObjectDef::ZObjectDef(bool isCase, std::string zId)
		: isCase_(isCase), ZIdSymbol(std::move(zId), Z_OBJECT_DEF) {}

	void ZObjectDef::setModifiers(sp<ZModifiers> mods) { modifiers_ = mods; }

	void ZObjectDef::setClassTemplate(sp<ZClassTemplate> ct) { classTemplate_ = ct; }

	// ── ZAccessModifier ───────────────────────────────────────────────────
	ZAccessModifier::ZAccessModifier() : ZSymbol(Z_ACCESS_MODIFIER) {}

	// ── ZClassDef ─────────────────────────────────────────────────────────
	ZClassDef::ZClassDef(std::string zId) : ZIdSymbol(std::move(zId), Z_CLASS_DEF) {}

	void ZClassDef::setModifiers(sp<ZModifiers> mods) { modifiers_ = mods; }

	sp<ZVariantTypeParamList> ZClassDef::getVariantTypeParamList() { return typeParams_; }

	void ZClassDef::setVariantTypeParamList(sp<ZVariantTypeParamList> tpl) { typeParams_ = tpl; }

	sp<ZClassParamList> ZClassDef::getClassParamList() { return classParams_; }

	void ZClassDef::setClassParamList(sp<ZClassParamList> cpl) { classParams_ = cpl; }

	void ZClassDef::setClassTemplate(sp<ZClassTemplate> ct) { classTemplate_ = ct; }

	void ZClassDef::setConstrAccessModifier(sp<ZAccessModifier> acmod) {
		constrAccessModifier_ = acmod;
	}


	// ── ZThisFunc ─────────────────────────────────────────────────────────
	ZThisFunc::ZThisFunc() : ZFunc(Z_THIS_FUNC_DEF) {}

	void ZThisFunc::setParamClauses(sp<ZParamList> p) { paramList_ = p; }

	void ZThisFunc::setConstrBlock(sp<ZConstrBlock> cb) { constrBlock_ = cb; }

	// ── ZGenerator ────────────────────────────────────────────────────────
	ZGenerator::ZGenerator() : ZSymbol(Z_GENERATOR) {}

	void ZGenerator::setCasePattern1(sp<ZTreePostOrderSS> cp) { casePattern1_ = cp; }

	void ZGenerator::setInExpr(sp<ZTreePostOrderSS> ie) { inExpr_ = ie; }

	void ZGenerator::addGuard(sp<ZTreePostOrderSS> g) {
		if (guards_ == nullptr) {
			guards_ = ms<std::vector<std::shared_ptr<ZTreePostOrderSS>>>();
		}
		guards_->push_back(g);
	}

	void ZGenerator::addEndingPattern1(sp<ZTreePostOrderSS> ep) {
		if (endingPattern1s_ == nullptr) {
			endingPattern1s_ = ms<std::vector<std::shared_ptr<ZTreePostOrderSS>>>();
		}
		endingPattern1s_->push_back(ep);
	}

	void ZGenerator::addEndingExpr(sp<ZTreePostOrderSS> ee) {
		if (endingPattern1s_ == nullptr) {
			endingPattern1s_ = ms<std::vector<std::shared_ptr<ZTreePostOrderSS>>>();
		}
		endingPattern1s_->push_back(ee);
	}

	// ── ZFor ──────────────────────────────────────────────────────────────
	ZFor::ZFor() : ZSymbol(Z_FOR) {}

	void ZFor::addGenerator(sp<ZGenerator> g) { generators_.push_back(g); }

	void ZFor::setYieldExpr(sp<ZTreePostOrderSS> y) { yieldExpr_ = y; }

	// ── ZCompileUnit ──────────────────────────────────────────────────────
	ZCompileUnit::ZCompileUnit(std::string zId) : ZIdSymbol(std::move(zId), Z_COMPILATION_UNIT) {
		packgName_ = "_ROOT_PKG_";
	}

	void ZCompileUnit::setPackage(std::string n) { packgName_ += "." + n; }

	std::string ZCompileUnit::toString() {
		return "ZCompileUnit(" + getZId().strId() + ", Package: " + packgName_ +
			", Stmts: " + std::to_string(statements_ ? statements_->size() : 0) + ")";
	}

	// ── ZProgram ──────────────────────────────────────────────────────────
	ZProgram::ZProgram(std::string progName) : ZIdSymbol(std::move(progName), Z_PROGRAM) {}

	void ZProgram::addCompileUnit(sp<ZCompileUnit> cu) { compileUnits_.push_back(cu); }

	vecP<ZCompileUnit> ZProgram::getCompileUnits() { return compileUnits_; }

	std::string ZProgram::toString() {
		return "ZProgram(" + getZId().strId() +
			", CompileUnits: " + std::to_string(compileUnits_.size()) + ")";
	}


	/////////////////////////////////////////
	void ZClassDef::accept(std::shared_ptr<XVisitor> visitor, sp<XEnclSc> sc) {
		visitor->visit(std::static_pointer_cast<ZClassDef>(shared_from_this()),  sc);
	}

	void ZObjectDef::accept(std::shared_ptr<XVisitor> visitor, sp<XEnclSc> sc) {
		visitor->visit(std::static_pointer_cast<ZObjectDef>(shared_from_this()), sc);
	}

	void ZTraitDef::accept(std::shared_ptr<XVisitor> visitor, sp<XEnclSc> sc) {
		visitor->visit(std::static_pointer_cast<ZTraitDef>(shared_from_this()), sc);
	}

	void ZSymbol::accept(std::shared_ptr<XVisitor> visitor, sp<XEnclSc> sc) {
		visitor->visit(std::static_pointer_cast<ZSymbol>(shared_from_this()), sc);
	}




} // namespace zebra::ast::symbol

