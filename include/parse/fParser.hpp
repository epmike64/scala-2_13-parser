#pragma once


#include "parse/fParseHelp.hpp"
#include "ast/leaf/fCompileUnit.hpp"
#include "lex/fLexerIFace.hpp"
#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodKndE.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "lex/kind/fTKnd.hpp"
#include "lex/kind/fLangOperatorKind.hpp"
#include "ast/leaf/fClassDef.hpp"
#include "ast/leaf/fImport.hpp"
#include "ast/leaf/fLiteral.hpp"
#include "ast/leaf/fObjectDef.hpp"
#include "ast/leaf/fStableId.hpp"
#include "ast/leaf/fType.hpp"
#include "ast/leaf/fValueDef.hpp"
#include "lex/kind/fVariableMutabilityTypeE.hpp"
#include "util/fCommon.hpp"

namespace zebra::parse {

	using namespace zebra::ast::leaf;
	using namespace zebra::lex;
	using namespace zebra::util;

	class fParser {
	public:
		fParseHelp h;

		fParser(fLexerIFace& lexer)
			: h(lexer) {
		}
	private:
		sp<fTypeArgs> types();
		sp<fTraitDef>  traitDef(sp<fModifiers> mods);
		sp<fAstOprndNod> classObjectDef(bool isCase, sp<fModifiers> mods);
		sp<fAstOprndNod> tmplDef(sp<fModifiers> mods);
		sp<fAccessModifier> accessModifier();
		sp<fLocalModifier> localModifier();
		sp<fModifiers> modifiers();

		sp<vector<sp<fImportSelector>>> ImportSelectors();
		sp<fImport> importClause();
		std::vector<const fToken*> qualIds();
		sp<fPackage> packageClause();

		sp<fWhile> exprWhile(sp<fAst> a);

		void exprIF(sp<fAst> a);

		void exprUnderscore(sp<fAst> a);

		void exprTID(sp<fAst> a, bool isPostfixExpr);

		sp<fAstProdSubTreeN> exprs();
		void exprLParen(sp<fAst> a);

		sp<fParamType> simpleType();

		void simpleType_2(sp<fAst> a);

		void typeWith(sp<fAst> a);

		vector<sp<fParamType>> paramTypes(bool isSimpleType);

		void typeFatArrow(sp<fAst> a);

		void typeLBracket(sp<fAst> a);

		void typeLParen(sp<fAst> a, bool isSimpleType);

		sp<fAstNod> caseClauses();

		void exprLCURL(sp<fAst> a);

		sp<fAstProdSubTreeN> postfixExpr();


		void exprDot(sp<fAst> a);

		void exprFatArrow(sp<fAst> a);

		void exprAssign(sp<fAst> a);

		void exprOperator(sp<fAst> a);
		sp<fStableId> path();

		sp<fTry> exprTry(sp<fAst> a);

		sp<fThrow> exprThrow(sp<fAst> a);

		sp<fReturn> exprReturn(sp<fAst> a);

		sp<fFor> exprFor(sp<fAst> a);

		sp<fAstProdSubTreeN> pattern1();

		std::vector<sp<fGenerator>> generators();

		sp<fLiteral> literal();

		sp<fStableId> pathWithKwType();

		sp<fStableId> stableId(bool );

		sp<fStableId> stableId(bool isPath, bool withKwType);

		void exprTid(sp<fAst> a) ;
		void exprLit(sp<fAst> a);
		std::vector<const fToken*> ids();
		sp<fAstProdSubTreeN> pattern2();

		sp<fAstProdSubTreeN> pattern();

		sp<fAstProdSubTreeN> patterns();

		sp<fAstProdSubTreeN> pattern3();

		void pattern3Id(sp<fAst> a);

		sp<fType> type();
		sp<fValueDef> ValDcl(bool);

		sp<fAstNod> typeArgs();

		void exprLBracket(sp<fAst> a);

		sp<fAstNod> exprNEW();

		sp<fTemplate> classTemplate(bool amExtender, bool isTrait);

		sp<fBlock> block();

		sp<fValue> patDef(fVariableMutabilityTypeE mutabilityType, sp<fModifiers> mods);

		sp<fTypeParam> typeParam();

		sp<fTypeParam> typeParam2(sp<fTypeParam> p);

		std::vector<sp<fTypeParam>> funTypeParams();

		sp<fValue> varDef(sp<fModifiers> mods);

		sp<fFunSig> funSig();

		sp<fRegFunc> namedFun(sp<fModifiers> mods);

		sp<fParamClauses> paramClauses();

		std::vector<sp<fParam>> paramClause(bool isImplicit);

		sp<fParam> param();

		sp<fConstrBlock> constrBlock();

		sp<fThisFunc> thisFun(sp<fModifiers> mods);

		sp<fFunc> funDef(sp<fModifiers> mods);

		sp<fTypeDef> typeDef();

		sp<fAstOprndNod> blockOrTemplateStmt();

		sp<fTemplateBody> templateBody();

		sp<fClassParamClauses> classParamClauses();

		std::vector<sp<fClassParam>> classParamClause();

		sp<fParamType> paramType(bool isSimpleType);

		sp<fClassParam> classParam();

		sp<fClassParents> classParents(bool isTrait);

		sp<fClassConstr> classConstr(bool isTrait);

		sp<fVariantTypeParam> variantTypeParam();

		sp<fTypeParamClause> typeParamClause();

		sp<fTemplate> classExtends(bool isTrait);

		sp<fObjectDef> objectDef(bool isCase, sp<fModifiers> mods);
		sp<fClassDef> classDef(bool isCase, sp<fModifiers> mods);

		void classParamClauses2(sp<fClassParamClauses> cpcs);

		sp<fAstProdSubTreeN> expr(sp<fAst>);
	public:
		sp<fCompileUnit> compileUnit();
	};


}
