#include "parse/fParser.hpp"

#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fAccessQualifier.hpp"
#include "ast/leaf/fBlock.hpp"
#include "ast/leaf/fCaseClause.hpp"
#include "ast/leaf/fCaseClauses.hpp"
#include "ast/leaf/fClassConstr.hpp"
#include "ast/leaf/fClassParam.hpp"
#include "ast/leaf/fClassParents.hpp"
#include "ast/leaf/fClassTemplate.hpp"
#include "ast/leaf/fConstrBlock.hpp"
#include "ast/leaf/fFor.hpp"
#include "ast/leaf/fFunSig.hpp"
#include "ast/leaf/fGenerator.hpp"
#include "ast/leaf/fId.hpp"
#include "ast/leaf/fIf.hpp"
#include "ast/leaf/fImport.hpp"
#include "ast/leaf/fLiteral.hpp"
#include "ast/leaf/fLocalModifier.hpp"
#include "ast/leaf/fNamedFun.hpp"
#include "ast/leaf/fOverrideModifier.hpp"
#include "ast/leaf/fPackage.hpp"
#include "ast/leaf/fParam.hpp"
#include "ast/leaf/fParamClauses.hpp"
#include "ast/leaf/fParamTypes.hpp"
#include "ast/leaf/fReturn.hpp"
#include "ast/leaf/fTemplate.hpp"
#include "ast/leaf/fTemplateBody.hpp"
#include "ast/leaf/fThisFun.hpp"
#include "ast/leaf/fThrow.hpp"
#include "ast/leaf/fTry.hpp"
#include "ast/leaf/fTypeArgs.hpp"
#include "ast/leaf/fTypeDef.hpp"
#include "ast/leaf/fUnderscore.hpp"
#include "ast/leaf/fValueDecl.hpp"
#include "ast/leaf/fValueDef.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
#include "ast/leaf/fWhile.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "lex/kind/fLangPseudoOperatorKindE.hpp"

namespace zebra::parse {


	sp<fTry> fParser::exprTry(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_TRY);
				sp<fTry> tr = ms<fTry>(expr(nullptr));
				if (h.isTkCatch()) {
					h.next();
					tr->setCatchBlock(expr(nullptr));
				}
				if(h.isTkFinally()){
					h.next();
					tr->setFinallyBlock(expr(nullptr));
				}
				return tr;
			}
			default:
				throw std::runtime_error("Try in unexpected place: " );
		}
	}

	sp<fThrow> fParser::exprThrow(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_THROW);
				return ms<fThrow>(expr(nullptr));
			}
			default:
				throw std::runtime_error("Throw in unexpected place: ");
		}
	}


	sp<fReturn> fParser::exprReturn(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_RETURN);
				sp<fReturn> ret = ms<fReturn>();
				switch (*h.tKnd()) {
					case fTKnd::T_IF_E: case fTKnd::T_WHILE_E: case fTKnd::T_FOR_E: case fTKnd::T_TRY_E: case fTKnd::T_THROW_E: case fTKnd::T_RETURN_E:
					case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: case fTKnd::T_LCURL_E: case fTKnd::T_NEW_E: {
						ret->setReturnExpr(expr(nullptr));
						break;
					}
					default:
						break;
				}
				return ret;
			}
			default:
				throw std::runtime_error("Return in unexpected place: " );
		}
	}

	sp<fFor> fParser::exprFor(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_FOR);
				sp<fFor> f4 = nullptr;
				switch (*h.tKnd()) {
					case fTKnd::T_LPAREN_E: {
						int sz = h.pushNLEnabled(false);
						h.accept(fTKnd::T_LPAREN);
						f4 = ms<fFor>(generators());
						h.popNLEnabled(sz, false);
						h.accept(fTKnd::T_RPAREN);
						break;
					}
					case fTKnd::T_LCURL_E: {
						int sz = h.pushNLEnabled(true);
						h.accept(fTKnd::T_LCURL);
						f4 = ms<fFor>(generators());
						h.popNLEnabled(sz, true);
						h.accept(fTKnd::T_RCURL);
						break;
					}
					default:
						throw std::runtime_error("Expected '(' or '{' after 'for' but found: " + h.getToken()->toString());
				}
				h.skipAllNLs();
				if (h.isTkYield()) {
					h.next();
					f4->setYield(true);
				}
				f4->setYieldExpr(expr(nullptr));
				return f4;
			}
			default:
				throw std::runtime_error("For in unexpected place: ");
		}
	}

	sp<fAstProdSubTreeN> fParser::pattern1() {
		sp<fAst> a = ms<fAst>();

		if(h.isLa(1, fTKnd::T_COLON)){ //Multiple parse tree possible: SimplePattern {id [nl] SimplePattern}
			switch(*h.tKnd()){
				case fTKnd::T_UNDERSCORE_E: {
					a->setRight(ms<fUnderscore>(h.next()));
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_COLON, h.next());
					a->setRight(type());
					break;
				}
				case fTKnd::T_ID_E: {
					a->setRight(stableId(false));
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_COLON, h.next());
					a->setRight(type());
					break;
				}
				default:
					throw std::runtime_error("Pattern1 in unexpected place: " + h.getToken()->toString());
			}
		} else {
			a->setRight(pattern2());
		}
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::PATTERN_1, std::move(a->astRootOpr()));
	}

	std::vector<sp<fGenerator>> fParser::generators() {
		std::vector<sp<fGenerator>> gens;

		outerLoopTop:
		while (true) {
			bool isCase = false;
			if (h.isTkCase()) {
				h.next();
				isCase = true;
			}
			sp<fGenerator> g = ms<fGenerator>(pattern1(), isCase);
			gens.push_back(g);
			h.accept(fTKnd::T_IN);
			g->setInExpr(expr(nullptr));
			innerLoopTop:
			while (true) {
				bool gotSemi = h.skipSemi();
				switch (*h.tKnd()) {
					case fTKnd::T_CASE_E: {
						if(!gotSemi) throw std::runtime_error("Semi expected");
						goto outerLoopTop;
					}
					case fTKnd::T_IF_E: {
						h.next();
						g->addGuard(postfixExpr());
						goto innerLoopTop;
					}
					case fTKnd::T_UNDERSCORE_E: case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E:
					case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E:
					case fTKnd::T_NULL_E: {
						if(gotSemi) goto outerLoopTop;
						g->addEndingPattern1(pattern1());
						h.accept(fTKnd::T_ASSIGN);
						g->addEndingExpr(expr(nullptr));
						goto innerLoopTop;
					}
					default:
						goto outerLoopBottom;
				}
			}
		}
		outerLoopBottom:
		return gens;
	}

	sp<fLiteral> fParser::literal() {
		switch (*h.tKnd()) {
			case fTKnd::T_INT_LIT_E:
			case fTKnd::T_FLOAT_LIT_E:
			case fTKnd::T_STRING_LIT_E:
			case fTKnd::T_CHAR_LIT_E:
			case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E:
			case fTKnd::T_NULL_E: {
				const fTKnd* k = h.tKnd();
				return ms<fLiteral>(h.next(), k);
			}
			default:
				throw std::runtime_error("Expected literal but found: " + h.getToken()->toString());
		}
	}

	sp<fStableId> fParser::pathWithKwType() {
		return stableId(true, true);
	}

	sp<fStableId> fParser::path() {
		return stableId(true, false);
	}

	void fParser::exprTid(sp<fAst> a) {
		exprTID(a, false);
	}


	sp<fStableId> fParser::stableId(bool isPath) {
		return stableId(isPath, false);
	}

	sp<fStableId> fParser::stableId(bool isPath, bool withKwType) {
		if(h.tKnd() != fTKnd::T_ID && h.tKnd() != fTKnd::T_THIS && h.tKnd() != fTKnd::T_SUPER)
			throw std::runtime_error("Expected identifier, 'this' or 'super' but found: " + h.getToken()->toString());

		sp<fStableId> sid = ms<fStableId>(isPath);
	
		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_DOT_E: {
					if (h.isLa(1, {fTKnd::T_ID, fTKnd::T_SUPER, fTKnd::T_THIS}) || withKwType && h.isLa(1, fTKnd::T_TYPE)) {
						h.next();
						continue;
					}
					goto whl_bottom;
				}
				case fTKnd::T_ID_E: {
					sid->addTId(h.next());
					if (h.isTkDot()) continue;
					goto whl_bottom;
				}
				case fTKnd::T_THIS_E: {
					sid->addThis(h.next());
					if (h.isTkDot()) continue;
					goto whl_bottom;
				}
				case fTKnd::T_SUPER_E: {
					sid->addSuper(h.next());
					if (h.isTkLBracket()) {
						int n = h.pushNLEnabled(false);
						h.accept(fTKnd::T_LBRACKET);
						sid->addClassQualifier(h.accept(fTKnd::T_ID));
						h.popNLEnabled(n, false);
						h.accept(fTKnd::T_RBRACKET);
					}
					if (h.isTkDot()) continue;
					goto whl_bottom;
				}
				default:
					goto whl_bottom;
			}
		}
		whl_bottom:
		fTKnd* last = sid->getLastTKind();
		if (!isPath) {
			assert(last == fTKnd::T_ID);
		} else {
			assert(last == fTKnd::T_ID || last == fTKnd::T_THIS);
		}
		return sid;
	}

	sp<fWhile> fParser::exprWhile(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_WHILE);
				h.accept(fTKnd::T_LPAREN);
				sp<fWhile> ff = ms<fWhile>(expr(nullptr));
				h.accept(fTKnd::T_RPAREN);
				ff->setWhileBody(expr(nullptr));
				return ff;
			}
			default:
				throw std::runtime_error("While in unexpected place: ");
		}
	}


	void fParser::exprIF(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR:
			case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_IF);
				int sz = h.pushNLEnabled(false);
				h.accept(fTKnd::T_LPAREN);
				sp<fIf> ff = ms<fIf>(expr(nullptr));
				h.popNLEnabled(sz, false);
				h.accept(fTKnd::T_RPAREN);
				h.skipAllNLs();
				ff->setIfBody(expr(nullptr));
				h.skipSemi();
				if (h.isTkElse()) {
					h.next();
					ff->setElseBody(expr(nullptr));
				}
				a->setRight(std::move(ff));
				break;
			}
			default:
				throw std::runtime_error("Unexpected AST node kind: " + std::to_string(static_cast<int>(a->astLastNKnd())));
		}
	}


	void fParser::exprUnderscore(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				a->setRight(ms<fUnderscore>(h.next()));
				break;
			}
			case fAstNodKndE::AST_OPERAND:{
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_ETA_EXPANSION, h.getToken());
				a->setRight(ms<fUnderscore>(h.next()));
				break;
			}
			default:
				throw std::runtime_error("Underscore in unexpected place: ");
		}
	}

	void fParser::exprTID(sp<fAst> a, bool isPostfixExpr) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				a->setRight(path());
				break;
			}
			case fAstNodKndE::AST_OPERAND: {
				if (h.isTkId()) {
					if (!isPostfixExpr && h.isTkColon()) {
						h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_COLON, h.next());
						a->setRight(type());
						a->setIsContinue(false);

					} else if (!isPostfixExpr && h.isTkAssign()) {
						h.insertOperator(a, fLangOperatorKind::O_ASSIGN, h.next());
						a->setRight(expr(a));
						a->setIsContinue(false);
					} else {
						// h.insertOperator(a, fLangOperatorKind.getIdSymbolicAssoc(h.getAsNamedToken().isRightAssociative()), h.next());
						h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_ID, h.next());
						h.skipNL();
					}
					break;
				}
				// fall through
			}
			default:
				throw std::runtime_error("TID in unexpected place: " );
		}
	}

	void fParser::exprLit(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR:
			case fAstNodKndE::AST_OPERATOR:
				a->setRight(ms<fLiteral>(h.getToken(), h.tKnd()));
				h.next();
				break;
			default:
				throw std::runtime_error("Unexpected AST node kind: " + std::to_string(static_cast<int>(a->astLastNKnd())));
		}
	}

	void fParser::exprOperator(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				const fLangOperatorKind* opr = fLangOperatorKind::getLangOptr(h.tKnd());
				h.insertOperator(a, opr, h.next());
				h.skipNL();
				break;
			}
			default:
				throw std::runtime_error("Unexpected AST node kind: " + std::to_string(static_cast<int>(a->astLastNKnd())));
		}
	}

	sp<fAstProdSubTreeN> fParser::exprs() {
		sp<fAst> box = ms<fAst>();
		sp<fAst> curr = nullptr;
		int lparSz = 0;
		assert(h.isTkLParen());
		int sz = 0;
		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_LPAREN_E: {
					sz = h.pushNLEnabled(false);
					h.accept(fTKnd::T_LPAREN);
					lparSz++;
					continue;
				}
				default:
					goto out_wlp1;
			}
		}
		out_wlp1:

		int prevLParSz = lparSz;
		while (true) {
			box->setRight(expr(curr));

			while(h.isTkComma()){
				h.insertOperator(box, fLangOperatorKind::O_COMMA, h.next());
				box->setRight(expr(nullptr));
			}

			while (true) {
				switch (*h.tKnd()) {
					case fTKnd::T_RPAREN_E: {
						h.popNLEnabled(sz--, false);
						h.accept(fTKnd::T_RPAREN);
						lparSz--;
						if (lparSz == 0) {
							goto out_wlp2;
						}
						continue;
					}
					default:
						goto out_wlp2;
				}
			}
			out_wlp2:
			assert(lparSz >= 0);
			assert(prevLParSz > lparSz && "Unclosed right parentheses");
			prevLParSz = lparSz;
			if(lparSz == 0) {
				return ms<fAstProdSubTreeN>(fLangGrmrProdE::EXPRS_OR_BINDINGS, std::move(box->astRootOpr()));
			}
			curr = box;
			box = ms<fAst>();
		}
	}




	void fParser::exprLParen(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERATOR:
			case fAstNodKndE::AST_ROOT_OPERATOR: {
				a->setRight(exprs());
				break;
			}
			case fAstNodKndE::AST_OPERAND: {
				h.insertOperator(a, fLangOperatorKind::O_PARENS, h.getToken());
				a->setRight(exprs());
				break;
			}
			default:
				throw std::runtime_error("Unexpected AST node kind: " + std::to_string(static_cast<int>(a->astLastNKnd())));
		}
	}

	void fParser::typeWith(sp<fAst> a) {
		while (h.isTkWith()) {
			switch (a->astLastNKnd()) {
				case fAstNodKndE::AST_OPERAND: {
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_WITH, h.next());
					a->setRight(type());
					continue;
				}
				default:
					throw std::runtime_error("With in unexpected place: " );
			}
		}
	}

	sp<fParamType> fParser::simpleType() {
		sp<fAst> a = ms<fAst>();
		simpleType_2(a);
		return ms<fParamType>(ms<fType>(ms<fAstProdSubTreeN>(fLangGrmrProdE::SIMPLE_TYPE, std::move(a->astRootOpr()))), false, false);
	}

	void fParser::simpleType_2(sp<fAst> a) {

		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_ID_E: {
					switch (a->astLastNKnd()) {
						case fAstNodKndE::AST_OPERAND: {
							goto whl_bottom;
						}
						default:
							break;
					}
				}
					// fall through
				case fTKnd::T_SUPER_E: case fTKnd::T_THIS_E: {
					sp<fStableId> sid = path();
					a->setRight(sid);
					if (h.isTkDot() && h.isLa(1, fTKnd::T_TYPE)) {
						h.next(); h.next();
						sid->setSingletonType(true);
					}
					continue;
				}
				case fTKnd::T_LPAREN_E: {
					typeLParen(a, true);
					if (a->isContinue()) continue;
					goto whl_bottom;
				}
				case fTKnd::T_LBRACKET_E: {
					typeLBracket(a);
					continue;
				}
				default:
					goto whl_bottom;
			}
		}
		whl_bottom:
		return;
	}

	sp<fTypeArgs> fParser::types() {
		std::vector<sp<fType>> types;
		while (true) {
			types.push_back(type());
			if (h.isTkComma()) {
				h.next();
				continue;
			}
			break;
		}
		return ms<fTypeArgs>(std::move(types));
	}

	std::vector<sp<fParamType>> fParser::paramTypes(bool isSimpleType) {
		std::vector<sp<fParamType>> ps;
		while (true) {
			ps.push_back(paramType(isSimpleType));
			if (h.isTkComma()) {
				h.next();
				//h.insertOper(a, fLangOperKind.O_COMMA, h.next());
				continue;
			}
			break;
		}
		return ps;
	}

	void fParser::typeFatArrow(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_FAT_ARROW, h.next());
				a->setRight(type());
				break;
			}
			default:
				throw std::runtime_error("FatArrow in unexpected place: ");
		}
	}

	void fParser::typeLBracket(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				int sz = h.pushNLEnabled(false);
				h.insertPseudoOperator(a,fLangPseudoOperatorKindE::O_BRACKETS, h.accept(fTKnd::T_LBRACKET));
				a->setRight(types());
				h.popNLEnabled(sz, false);
				h.accept(fTKnd::T_RBRACKET);
				break;
			}
			default:
				throw std::runtime_error("LBracket in unexpected place: ");
		}
	}


	void fParser::typeLParen(sp<fAst> a, bool isSimpleType) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				h.accept(fTKnd::T_LPAREN);
				std::vector<sp<fParamType>> ps = paramTypes(isSimpleType);
				a->setRight(std::dynamic_pointer_cast<fAstOprndNod>(ms<fParamTypes>(std::make_shared<std::vector<sp<fParamType>>>(std::move(ps)))));
				h.accept(fTKnd::T_RPAREN);
				break;
			}
			case fAstNodKndE::AST_OPERAND: {
				a->setIsContinue(false);
				break;
			}
			default:
				throw std::runtime_error("LParen in unexpected place: ");
		}
	}

	sp<fAstNod> fParser::caseClauses() {
		std::vector<sp<fCaseClause>> clauses;
		while (h.isTkCase()) {
			h.next();
			sp<fCaseClause> cc = ms<fCaseClause>(pattern());
			clauses.push_back(cc);
			if (h.isTkIF()) {
				h.next();
				cc->setGuard(postfixExpr());
			}
			h.accept(fTKnd::T_FAT_ARROW);
			cc->setBlock(block());
		}
		return std::dynamic_pointer_cast<fAstNod>(ms<fCaseClauses>(std::move(clauses)));
	}

	void fParser::exprLCURL(sp<fAst> a) {
		int sz = h.pushNLEnabled(true);
		h.accept(fTKnd::T_LCURL);
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_CURLY_BRACES, h.getToken());
				//fall through
			}
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {

				if (h.tKnd() == fTKnd::T_CASE) {
					a->setRight(caseClauses());
				} else {
					a->setRight(block());
				}
				break;
			}
			default:
				throw std::runtime_error("LCURL in unexpected place: ");
		}
		h.popNLEnabled(sz, true);
		h.accept(fTKnd::T_RCURL);
	}


	sp<fAstProdSubTreeN> fParser::postfixExpr() {
		sp<fAst> a = ms<fAst>();
		bool isPlusMinus;
		loop:
		while (true) {
			isPlusMinus = false;
			switch (*h.tKnd()) {
				case fTKnd::T_NEW_E: {
					a->setRight(exprNEW());
					continue;
				}
				case fTKnd::T_NL_E: {
					if(!h.isLa(1, fTKnd::T_LCURL)) {
						goto out_wlp;
					}
					h.next();
					// fall through
				}
				case fTKnd::T_LCURL_E: {
					exprLCURL(a);
					continue;
				}
				case fTKnd::T_DOT_E: {
					exprDot(a);
					continue;
				}
				case fTKnd::T_PLUS_E: case fTKnd::T_MINUS_E: {
					isPlusMinus = true;
					//fall through
				}
				case fTKnd::T_TILDE_E: case fTKnd::T_EXCLAMATION_E: { //PrefixOperator  :: '-' | '+' | '~' | '!'
					if(a->astLastNKnd() == fAstNodKndE::AST_ROOT_OPERATOR || a->astLastNKnd() == fAstNodKndE::AST_OPERATOR){
						switch(*h.lookAhead(1)->getTKind()){
							case fTKnd::T_NEW_E: case fTKnd::T_LCURL_E: case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: case fTKnd::T_UNDERSCORE_E:
							case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: case fTKnd::T_NULL_E:{
								h.next();
								continue; //prefix operator
							}
							default:
								throw std::runtime_error("Unexpected token after prefix operator: " + h.getToken()->toString());
						}
					} else if(!isPlusMinus){
						throw std::runtime_error("Unexpected token after prefix operator: " + h.getToken()->toString());
					}
					// fall through
				}
				case fTKnd::fTKnd::T_STAR_E: case fTKnd::fTKnd::T_FORWARD_SLASH_E: case fTKnd::fTKnd::T_PERCENT_E:
				case fTKnd::T_LT_E: case fTKnd::T_LTE_E: case fTKnd::T_GT_E: case fTKnd::T_GTE_E: case fTKnd::T_EQUAL_E: case fTKnd::T_NOT_EQUAL_E:
				case fTKnd::T_LOGICAL_AND_E:  case fTKnd::T_LOGICAL_OR_E: {
					exprOperator(a);
					continue;
				}
				case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E:
				case fTKnd::T_NULL_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: {
					exprLit(a);
					continue;
				}
				case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: {
					exprTID(a, true);
					continue;
				}
				case fTKnd::T_LPAREN_E: {
					exprLParen(a);
					continue;
				}
				case fTKnd::T_LBRACKET_E: {
					exprLBracket(a);
					continue;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::POSTFIX_EXPR, std::move(a->astRootOpr()));
	}

	void fParser::exprDot(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_DOT, h.next());
				a->setRight(std::dynamic_pointer_cast<fAstNod>(ms<fId>(h.accept(fTKnd::T_ID))));
				break;
			}
			default:
				throw std::runtime_error("Dot in unexpected place: " );
		}
	}

	// sp<fAstProdSubTreeN> fParser::expr(sp<fAst> a) {
	// 	if (a == nullptr) a = ms<fAst>();
	//
	// 	while (true) {
	// 		switch (*h.tKnd()) {
	//
	// 			case fTKnd::T_NL_E: {
	// 				if (!h.isLa(1, fTKnd::T_LCURL)) {
	// 					goto out_whp;
	// 				}
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_IF_E: {
	// 				exprIF(a);
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_WHILE_E: {
	//
	// 			}
	//
	// 			case fTKnd::T_FOR_E: {
	//
	// 			}
	//
	// 			case fTKnd::T_FAT_ARROW_E:{}
	// 			case fTKnd::T_RETURN_E: {}
	//
	//
	// 			case fTKnd::T_MATCH_E: {}
	//
	// 			case fTKnd::T_LBRACKET_E: {
	// 			}
	// 			case fTKnd::T_ASSIGN_E: {}
	// 			case fTKnd::T_NEW_E:{}
	// 			case fTKnd::T_LCURL_E:{}
	// 			case fTKnd::T_DOT_E:{}
	//
	//
	// 			case fTKnd::T_LPAREN_E: {
	// 				exprLParen(a);
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_TILDE_E:
	// 			case fTKnd::T_EXCLAMATION_E:{}
	//
	// 			case fTKnd::T_PLUS_E:
	// 			case fTKnd::T_MINUS_E:
	// 			case fTKnd::T_STAR_E:
	// 			case fTKnd::T_FORWARD_SLASH_E:
	// 			case fTKnd::T_PERCENT_E: {
	// 				exprOperator(a);
	// 				continue;
	// 			}
	//
	//
	// 			case fTKnd::T_EQUAL_E:
	// 			case fTKnd::T_NOT_EQUAL_E:
	// 			case fTKnd::T_LT_E:
	// 			case fTKnd::T_LTE_E:
	// 			case fTKnd::T_GT_E:
	// 			case fTKnd::T_GTE_E: {
	// 				exprOperator(a);
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_LOGICAL_AND_E:
	// 			case fTKnd::T_LOGICAL_OR_E: {
	// 				exprOperator(a);
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_INT_LIT_E:
	// 			case fTKnd::T_FLOAT_LIT_E:
	// 			case fTKnd::T_CHAR_LIT_E:
	// 			case fTKnd::T_STRING_LIT_E:
	// 			case fTKnd::T_TRUE_E:
	// 			case fTKnd::T_FALSE_E:
	// 			case fTKnd::T_NULL_E:{
	// 				exprLit(a);
	// 				continue;
	// 			}
	//
	// 			case fTKnd::T_ID_E: {
	// 				exprTid(a);
	// 				continue;
	// 			}
	// 			case fTKnd::T_THIS_E:
	// 			case fTKnd::T_SUPER_E: {}
	//
	//
	//
	// 			default:
	// 				goto out_whp;
	// 		}
	// 	}
	// 	out_whp:
	//
	// 	return ms<fAstProdSubTreeN>(fLangGrmrProdE::EXPR, std::move(a->astRootOpr()));
	// }

	void fParser::exprFatArrow(sp<fAst> a) {
		switch (a->astLastNKnd()){
			case fAstNodKndE::AST_OPERAND: {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_FAT_ARROW, h.next());
				a->setRight(expr(nullptr));
				break;
			}
			default:
				throw std::runtime_error("FatArrow in unexpected place: ");
		}
	}

	void fParser::exprAssign(sp<fAst> a) {
		switch (a->astLastNKnd()){
			case fAstNodKndE::AST_OPERAND: {
				h.insertOperator(a, fLangOperatorKind::O_ASSIGN, h.next());
				a->setRight(expr(nullptr));
				break;
			}
			default:
				throw new std::runtime_error("Assign in unexpected place: ");
		}
	}

	sp<fAstProdSubTreeN> fParser::expr(sp<fAst> a) {
		if (a == nullptr) a = ms<fAst>();
		bool isPlusMinus = false;

		while (true) {
			isPlusMinus = false;
			switch (*h.tKnd()) {
				case fTKnd::T_IF_E: {
					exprIF(a);
					goto out_wlp;
				}
				case fTKnd::T_WHILE_E: {
					a->setRight(exprWhile(a));
					goto out_wlp;
				}
				case fTKnd::T_FOR_E: {
					a->setRight(exprFor(a));
					goto out_wlp;
				}
				case fTKnd::T_TRY_E: {
					a->setRight(exprTry(a));
					goto out_wlp;
				}
				case fTKnd::T_THROW_E: {
					a->setRight(exprThrow(a));
					goto out_wlp;
				}
				case fTKnd::T_RETURN_E: {
					a->setRight(exprReturn(a));
					goto out_wlp;
				}

				case fTKnd::T_MATCH_E: {
					h.next();
					int sz = h.pushNLEnabled(true);
					h.accept(fTKnd::T_LCURL);
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_MATCH, h.getToken());
					a->setRight(caseClauses());
					h.popNLEnabled(sz, true);
					h.accept(fTKnd::T_RCURL);
					goto out_wlp;
				}
				case fTKnd::T_LBRACKET_E: {
					exprLBracket(a); //typeArgs
					goto out_wlp;
				}
				case fTKnd::T_LPAREN_E: {// function() ArgumentExprs
					exprLParen(a);
					if (h.isLa(0, fTKnd::T_FAT_ARROW)) {
						h.insertPseudoOperator(a,  fLangPseudoOperatorKindE::O_FAT_ARROW, h.next());
						a->setRight(expr(nullptr));
						goto out_wlp;
					}
					continue;
				}
				case fTKnd::T_FAT_ARROW_E: {
					exprFatArrow(a);
					continue;
				}
				case fTKnd::T_ASSIGN_E: {
					exprAssign(a);
					continue;
				}
				case fTKnd::T_NEW_E: {
					a->setRight(exprNEW());
					continue;
				}
				case fTKnd::T_NL_E: {
					if (!h.isLa(1, fTKnd::T_LCURL)) {
						goto out_wlp;
					}
					h.next();
					// fall through
				}
				case fTKnd::T_LCURL_E: {
					exprLCURL(a);
					continue;
				}
				case fTKnd::T_DOT_E: {
					exprDot(a);
					continue;
				}
				case fTKnd::T_PLUS_E: case fTKnd::T_MINUS_E: {
					isPlusMinus = true;
					//fall through
				}
				case fTKnd::T_TILDE_E: case fTKnd::T_EXCLAMATION_E: {
					if (a->astLastNKnd() == fAstNodKndE::AST_ROOT_OPERATOR || a->astLastNKnd() == fAstNodKndE::AST_OPERATOR) {
						switch (*h.lookAhead(1)->getTKind()) {
							case fTKnd::T_NEW_E: case fTKnd::T_LCURL_E: case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: case fTKnd::T_UNDERSCORE_E:
							case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: case fTKnd::T_NULL_E: {
								h.next(); continue; //prefix operator
							}
							default:
								throw std::runtime_error("Unexpected token after prefix operator: " + h.getToken()->toString());
						}
					} else if (!isPlusMinus) {
						throw std::runtime_error("Unexpected token after prefix operator: " + h.getToken()->toString());
					}
					//fall through
				}
				case fTKnd::T_STAR_E: case fTKnd::T_FORWARD_SLASH_E: case fTKnd::T_PERCENT_E: {
					exprOperator(a);
					continue;
				}
				case fTKnd::T_LT_E: case fTKnd::T_LTE_E: case fTKnd::T_GT_E: case fTKnd::T_GTE_E: case fTKnd::T_EQUAL_E: case fTKnd::T_NOT_EQUAL_E: {
					exprOperator(a);
					continue;
				}
				case fTKnd::T_LOGICAL_AND_E: case fTKnd::T_LOGICAL_OR_E:{
					exprOperator(a);
					continue;
				}
				case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: case fTKnd::T_NULL_E: {
					exprLit(a);
					continue;
				}
					/*
					  Expr :: (Bindings | ['implicit'] (id|'_')) => Expr
					  ResultExpr :: (Bindings | ['implicit'] (id|'_')) [':' CompoundType] => Block
					 */
				case fTKnd::T_IMPLICIT_E: {
					if (h.isLa(1, {fTKnd::T_UNDERSCORE, fTKnd::T_ID})) {
						h.next();
						if (h.isTkUnderscore()) {
							exprUnderscore(a);
						} else {
							exprTID(a, false);
						}
						if (h.isTkColon()) {
							h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_COLON, h.next());
							a->setRight(type());
						}
						continue;
					}
					throw std::runtime_error("Unexpected token after 'implicit': " + h.getToken()->toString());
				}
				case fTKnd::T_UNDERSCORE_E: {
					exprUnderscore(a);
					if (h.isTkColon()) {  // Binding ::= (id | '_') [':' Type]
						h.insertPseudoOperator(a,  fLangPseudoOperatorKindE::O_COLON, h.next());
						a->setRight(type());
					}
					continue;
				}
				case fTKnd::T_ID_E: {
					exprTID(a, false);
					if (h.isTkColon()) {  // Binding ::= (id | '_') [':' Type]
						h.insertPseudoOperator(a,  fLangPseudoOperatorKindE::O_COLON, h.next());
						a->setRight(type());
					}
					continue;
				}
				case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: {
					exprTID(a, false);
					if (a->isContinue()) continue;
					goto out_wlp;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::EXPR, std::move(a->astRootOpr()));
	}



	sp<fObject> fParser::objectDef(bool isCase, sp<fModifiers> mods) {
		h.accept(fTKnd::T_OBJECT);
		sp<fObject> obj = ms<fObject>(h.next(), std::move(mods), isCase);
		obj->setExtendsTemplate(classExtends(false));
		return obj;
	}

	sp<fType> fParser::type() {
		sp<fAst> a = ms<fAst>();

		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_ID_E: {
					switch (a->astLastNKnd()) {
						case fAstNodKndE::AST_OPERAND: {
							// h.insertOperator(a, fLangOperatorKind.getIdSymbolicAssoc(h.getAsNamedToken().isRightAssociative()), h.next());
							//h.insertMethodNameOperator(a, h.next());
							h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_ID, h.next());
							continue;
						}
						default:
							break;
					}
					//fall through
				}
				case fTKnd::T_SUPER_E: case fTKnd::T_THIS_E: case fTKnd::T_LPAREN_E: {
					simpleType_2(a);
					continue;
				}

				case fTKnd::T_FAT_ARROW_E: {
					if (h.isLa(1, {fTKnd::T_ID, fTKnd::T_SUPER, fTKnd::T_THIS, fTKnd::T_LPAREN})) {
						typeFatArrow(a);
					}
					goto out_wlp;
				}
				case fTKnd::T_WITH_E: {
					typeWith(a);
					continue;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		return ms<fType>(ms<fAstProdSubTreeN>(fLangGrmrProdE::TYPE, std::move(a->astRootOpr())));
	}


	sp<fAstProdSubTreeN> fParser::pattern2() {
		sp<fAst> a = ms<fAst>();

		switch (*h.tKnd()) {
			case fTKnd::T_ID_E: {
				if (h.isLa(1, fTKnd::T_AT)) {
					a->setRight(stableId(false));
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_AT, h.next());
					a->setRight(pattern3());
					return ms<fAstProdSubTreeN>(fLangGrmrProdE::SUBTREE, std::move(a->astRootOpr()));
				}
				//fall through
			}
			case fTKnd::T_UNDERSCORE_E: case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E:
			case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: case fTKnd::T_NULL_E:
			case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: {
				a->setRight(pattern3());
				return ms<fAstProdSubTreeN>(fLangGrmrProdE::PATTERN_2, std::move(a->astRootOpr()));
			}
			default:
				throw std::runtime_error("Pattern in unexpected place: " + h.getToken()->toString());
		}
	}

	sp<fAstProdSubTreeN> fParser::pattern() {
		sp<fAst> a = ms<fAst>();
		while (true) {
			a->setRight(pattern1());
			if (h.isTkPipe()) {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_PIPE, h.next());
				continue;
			}
			break;
		}
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::PATTERN, std::move(a->astRootOpr()));
	}

	sp<fAstProdSubTreeN> fParser::patterns() {
		sp<fAst> a = ms<fAst>();
		while (true) {
			a->setRight(pattern());
			if (h.isTkComma()) {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_COMMA, h.next());
				continue;
			}
			break;
		}
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::PATTERNS, std::move(a->astRootOpr()));
	}

	sp<fAstProdSubTreeN> fParser::pattern3() {
		sp<fAst> a = ms<fAst>();

		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_UNDERSCORE_E:{
					a->setRight(ms<fUnderscore>(h.next()));
					continue ;
				}
				case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: case fTKnd::T_NULL_E: {
					a->setRight(literal());
					continue;
				}
				case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: {
					pattern3Id(a);
					if(a->isContinue()) continue;
					goto whl_bottom;
				}
				case fTKnd::T_LPAREN_E: {
					if(a->astLastNKnd() == fAstNodKndE::AST_OPERAND){
						h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_PARENS, h.getToken());
					}
					int sz = h.pushNLEnabled(false);
					h.accept(fTKnd::T_LPAREN);
					a->setRight(patterns());
					h.popNLEnabled(sz, false);
					h.accept(fTKnd::T_RPAREN);
					continue;
				}
				default:
					goto whl_bottom;
			}
		}
		whl_bottom:
		return ms<fAstProdSubTreeN>(fLangGrmrProdE::PATTERN_3, std::move(a->astRootOpr()));
	}

	void fParser::pattern3Id(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_ROOT_OPERATOR: case fAstNodKndE::AST_OPERATOR: {
				a->setRight(stableId(false));
				break;
			}
			case fAstNodKndE::AST_OPERAND: {
				if(h.isTkTID()){
					// h.insertOperator(a, fLangOperatorKind.getIdSymbolicAssoc(h.getAsNamedToken().isRightAssociative()), h.next());
					// h.insertOperator(a, fLangOperatorKind.getIdSymbolicAssoc(h.getAsNamedToken().isRightAssociative()), h.next());
					// h.insertMethodNameOperator(a, h.next());
					h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_ID, h.next());
				} else {
					a->setIsContinue(false);
				}
				break;
			}
			default:
				throw std::runtime_error("Pattern3Id in unexpected place: " );
		}
	}

	std::vector<const fToken*> fParser::ids() {
		std::vector<const fToken*> idTokens;
		while (true) {
			idTokens.push_back(h.accept(fTKnd::T_ID));
			if (h.isTkComma()) {
				h.next(); continue;
			}
			break;
		}
		return idTokens;
	}

	sp<fAstNod> fParser::typeArgs() {
		h.accept(fTKnd::T_LBRACKET);
		sp<fTypeArgs> args = types();
		h.accept(fTKnd::T_RBRACKET);
		return std::dynamic_pointer_cast<fAstNod>(args);
	}

	void fParser::exprLBracket(sp<fAst> a) {
		switch (a->astLastNKnd()) {
			case fAstNodKndE::AST_OPERAND: {
				h.insertPseudoOperator(a, fLangPseudoOperatorKindE::O_BRACKETS, h.getToken());
				a->setRight(typeArgs());
				break;
			}
			default:
				throw std::runtime_error("LBracket in unexpected place: " );
		}
	}

	sp<fAstNod> fParser::exprNEW() {
		h.accept(fTKnd::T_NEW);
		switch (*h.tKnd()) {
			case fTKnd::T_LCURL_E: {
				return std::dynamic_pointer_cast<fAstNod>(ms<fTemplate>(templateBody(), false));
			}
			case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: {
				return classTemplate(false, false);
			}
			default:
				throw std::runtime_error("NEW in unexpected place: " + h.getToken()->toString());
		}
	}

	sp<fTemplate> fParser::classTemplate(bool amExtender, bool isTrait) {
		sp<fClassParents> cp = classParents(isTrait);
		if (h.isTkLCurl() || (h.isTkNL() && h.isLa(1, fTKnd::T_LCURL))) {
			return ms<fClassTemplate>(templateBody(), amExtender, std::move(cp));
		}
		return ms<fClassTemplate>(nullptr, amExtender, std::move(cp));
	}

	sp<fBlock> fParser::block() {
		sp<fBlock> block = ms<fBlock>();

		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_CASE_E: {
					if (!h.isLa(1, {fTKnd::T_CLASS, fTKnd::T_OBJECT})) {
						goto out_wlp;
					}
				}
					//fall through
				case fTKnd::T_IMPORT_E: case fTKnd::T_IMPLICIT_E: case fTKnd::T_LAZY_E: case fTKnd::T_ABSTRACT_E: case fTKnd::T_FINAL_E: case fTKnd::T_SEALED_E:
				case fTKnd::T_VAL_E: case fTKnd::T_VAR_E: case fTKnd::T_DEF_E: case fTKnd::T_TYPE_E: case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E: case fTKnd::T_TRAIT_E:
				case fTKnd::T_IF_E: case fTKnd::T_WHILE_E: case fTKnd::T_FOR_E: case fTKnd::T_TRY_E: case fTKnd::T_THROW_E: case fTKnd::T_RETURN_E: case fTKnd::T_NEW_E:
				case fTKnd::T_LCURL_E: case fTKnd::T_LPAREN_E: case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E:
				case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_NULL_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E: {
					block->addStmt(blockOrTemplateStmt());
					h.skipSemi();
					continue;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		return block;
	}

	sp<fValue> fParser::patDef(fVariableMutabilityTypeE mutabilityType, sp<fModifiers> mods) {
		sp<fValue> value = nullptr;
		switch (mutabilityType){
			case fVariableMutabilityTypeE::VAL: {
				value = ms<fValueDef>(std::move(mods));
				break;
			}
			case fVariableMutabilityTypeE::VAR: {
				value = std::dynamic_pointer_cast<fValue>(ms<fValueDecl>(std::move(mods)));
				break;
			}
			default:
				throw std::runtime_error("Expected 'val' or 'var' but found: " + h.getToken()->toString());
		}

		while (true) {
			value->addName(pattern2());
			if (h.isTkComma()) {
				h.next(); continue;
			}
			break;
		}
		if (h.isTkColon()) {
			h.next();
			value->setType(type());
		}
		if(h.isTkAssign()){
			h.next();
			value->setAssignExpr(expr(nullptr));
		}
		return value;
	}

	// sp<fTypeParam> fParser::typeParam() {
	// 	sp<fTypeParam> p = ms<fTypeParam>(h.next());
	// 	if (h.isTkLBracket()) {
	// 		p->setVariantTypeParams(variantTypeParams());
	// 	}
	// 	if (h.isTkLowerBound()) {
	// 		p->setLowerBound(type());
	// 	}
	// 	if (h.isTkUpperBound()) {
	// 		p->setUpperBound(type());
	// 	}
	// 	if (h.isTkColon()) {
	// 		p->setType(type());
	// 	}
	//
	// 	return p;
	// }

	std::vector<sp<fTypeParam>> fParser::funTypeParams() {
		std::vector<sp<fTypeParam>> params;
		int sz = h.pushNLEnabled(false);
		h.accept(fTKnd::T_LBRACKET);
		while (true) {
			params.push_back(typeParam());
			if (h.isTkComma()) {
				h.next();
				continue;
			}
			break;
		}
		h.popNLEnabled(sz, false);
		h.accept(fTKnd::T_RBRACKET);
		return params;
	}

	sp<fValue> fParser::varDef(sp<fModifiers> mods) {
		// patDef() + "ids: Type = _"
		return patDef(fVariableMutabilityTypeE::VAR, mods);
	}

	sp<fFunSig> fParser::funSig() {
		sp<fFunSig> fs = ms<fFunSig>(h.next());
		if (h.isTkLBracket()) {
			fs->setTypeParams(funTypeParams());
		}
		fs->setParamClauses(paramClauses());
		return fs;
	}

	sp<fNamedFun> fParser::namedFun(sp<fModifiers> mods) {
		sp<fNamedFun> fun = ms<fNamedFun>(std::move(mods), funSig());
		if (h.isTkColon()) {
			h.next();
			fun->setReturnType(type());
		}
		if (h.isTkAssign()) {
			h.next();
			fun->setFunBody(expr(nullptr));
		} else if (h.isTkLCurl()) {
			int sz = h.pushNLEnabled(true);
			h.accept(fTKnd::T_LCURL);
			fun->setFunBody(block());
			h.popNLEnabled(sz, true);
			h.accept(fTKnd::T_RCURL);
		}
		return fun;
	}

	sp<fParamClauses> fParser::paramClauses() {
		sp<fParamClauses> pcs = ms<fParamClauses>();
		while (h.isTkLParen()) {
			if (h.isLa(1, fTKnd::T_IMPLICIT)) {
				pcs->setImplicitParams(paramClause(true));
				break;
			}
			pcs->addParams(paramClause(false));
		}
		return pcs;
	}

	std::vector<sp<fParam>> fParser::paramClause(bool isImplicit) {
		std::vector<sp<fParam>> params;
		h.accept(fTKnd::T_LPAREN);
		if (!h.isTkRParen()) {
			if (isImplicit) {
				h.accept(fTKnd::T_IMPLICIT);
			}
			while (true) {
				params.push_back(param());
				if (h.isTkComma()) {
					h.next(); continue;
				}
				break;
			}
		}
		h.accept(fTKnd::T_RPAREN);
		return params;
	}

	sp<fParam> fParser::param() {
		sp<fParam> p = ms<fParam>(h.next());
		if (h.isTkColon()) {
			h.next();
			p->setParamType(paramType(false));
		}
		if (h.isTkAssign()) {
			h.next();
			p->setDefaultValue(expr(nullptr));
		}
		return p;
	}

	sp<fConstrBlock> fParser::constrBlock() {
		sp<fConstrBlock> cb = ms<fConstrBlock>();
		h.accept(fTKnd::T_LCURL);
		if (h.isTkTHIS()) {
			h.next();
			cb->setArgExprs(exprs());
		}
		while (true) {
			h.skipSemi();
			if (!h.isTkRParen()) {
				cb->addBlockStmt(blockOrTemplateStmt());
			} else {
				break;
			}
		}
		h.accept(fTKnd::T_RCURL);
		return cb;
	}

	sp<fThisFun> fParser::thisFun(sp<fModifiers> mods) {
		h.accept(fTKnd::T_THIS);
		sp<fThisFun> fun = ms<fThisFun>(std::move(mods));
		fun->setParamClauses(paramClauses());
		if (h.isTkAssign()) {
			h.next();
			sp<fConstrBlock> cb = nullptr;
			if (h.isTkTHIS()) {
				h.next();
				cb = ms<fConstrBlock>();
				cb->setArgExprs(exprs());
			} else if (h.isTkLCurl()) {
				cb = constrBlock();
			} else {
				throw std::runtime_error("Expected 'this' or '{' after '=' in function definition but found: " + h.getToken()->toString());
			}
			fun->setConstrBlock(std::move(cb));

		} else {

			fun->setConstrBlock(constrBlock());
		}
		return fun;
	}


	sp<fFun> fParser::funDef(sp<fModifiers> mods) {
		h.accept(fTKnd::T_DEF);
		switch (*h.tKnd()) {
			case fTKnd::T_ID_E: {
				return namedFun(mods);
			}
			case fTKnd::T_THIS_E: {
				return thisFun(mods);
			}
			default:
				throw std::runtime_error("Expected 'def' followed by identifier or 'this' but found: " + h.getToken()->toString());
		}
	}

	sp<fTypeDef> fParser::typeDef() {
		h.accept(fTKnd::T_TYPE);
		sp<fTypeDef> t = ms<fTypeDef>(h.next());
		if (h.isTkLBracket()) {
			t->setTypeParams(variantTypeParams());
		}
		h.accept(fTKnd::T_ASSIGN);
		t->setAssignedType(type());
		return t;
	}

	sp<fAstOprndNod> fParser::blockOrTemplateStmt() {

		if(h.isTkImport()){
			return importClause();
		}

		sp<fModifiers> mods = modifiers();

		switch (*h.tKnd()) {
			case fTKnd::T_CASE_E: case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E: case fTKnd::T_TRAIT_E: {
				return tmplDef(mods);
			}
			case fTKnd::T_VAL_E: {
				h.next();
				return patDef(fVariableMutabilityTypeE::VAL, mods);
			}
			case fTKnd::T_VAR_E: {
				h.next();
				return varDef(mods);
			}
			case fTKnd::T_DEF_E: {
				return funDef(mods);
			}
			case fTKnd::T_TYPE_E: {
				return typeDef();
			}
			case fTKnd::T_IF_E: case fTKnd::T_WHILE_E: case fTKnd::T_FOR_E: case fTKnd::T_TRY_E: case fTKnd::T_THROW_E: case fTKnd::T_RETURN_E:
			case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: case fTKnd::T_LCURL_E: case fTKnd::T_NEW_E:
			case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E: case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_TRUE_E: case fTKnd::T_FALSE_E:
			case fTKnd::T_NULL_E: {
				return expr(nullptr);
			}
			default:
				break;
		}

		throw std::runtime_error( "BlockOrTemplateStat in unexpected place: " + h.getToken()->toString());
	}

	sp<fTemplateBody> fParser::templateBody() {
		sp<fTemplateBody> tb = ms<fTemplateBody>();
		if (h.isTkNL()) h.next();
		int sz = h.pushNLEnabled(true);
		h.accept(fTKnd::T_LCURL);
		loop:
		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_IMPORT_E: case fTKnd::T_ABSTRACT_E: case fTKnd::T_FINAL_E: case fTKnd::T_SEALED_E: case fTKnd::T_IMPLICIT_E: case fTKnd::T_LAZY_E:
				case fTKnd::T_OVERRIDE_E: case fTKnd::T_PROTECTED_E: case fTKnd::T_PRIVATE_E:
				case fTKnd::T_VAL_E: case fTKnd::T_VAR_E: case fTKnd::T_DEF_E: case fTKnd::T_TYPE_E: case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E: case fTKnd::T_TRAIT_E:
				case fTKnd::T_IF_E: case fTKnd::T_WHILE_E: case fTKnd::T_FOR_E: case fTKnd::T_TRY_E: case fTKnd::T_THROW_E: case fTKnd::T_RETURN_E: case fTKnd::T_NEW_E:
				case fTKnd::T_LCURL_E: case fTKnd::T_LPAREN_E: case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_INT_LIT_E: case fTKnd::T_FLOAT_LIT_E:
				case fTKnd::T_STRING_LIT_E: case fTKnd::T_CHAR_LIT_E: case fTKnd::T_NULL_E: case fTKnd::T_TRUE_E: case fTKnd::fTKnd::T_FALSE_E: {
					tb->addStmt(blockOrTemplateStmt());
					h.skipSemi();
					continue;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		h.popNLEnabled(sz, true);
		h.accept(fTKnd::T_RCURL);
		return tb;
	}

	sp<fClassDef> fParser::classDef(bool isCase, sp<fModifiers> mods) {
		h.accept(fTKnd::T_CLASS);
		auto cls = std::make_shared<fClassDef>(h.next(), std::move(mods), isCase);
		if (h.isTkLBracket()) {
			cls->setTypeParams(variantTypeParams());
		}
		switch(*h.tKnd()){
			case fTKnd::T_PRIVATE_E: case fTKnd::T_PROTECTED_E: {
				cls->setConstrAccessModifier(accessModifier());
				break;
			}
			default:
				break;
		}
		cls->setClassParamClauses(classParamClauses());
		cls->setExtendsTemplate(classExtends(false));
		return cls;
	}

	void fParser::classParamClauses2(sp<fClassParamClauses> cpcs) {

		while (true) {

			if (h.isTkNL() && h.isLa(1, fTKnd::T_LPAREN)) {
				h.next(); h.next();
			} else if (h.isTkLParen()) {
				h.next();
			} else {
				goto out_wlp;
			}

			switch (*h.tKnd()) {
				case fTKnd::T_IMPLICIT_E: {
					h.next();
					cpcs->setImplicitParams(classParamClause());
					h.accept(fTKnd::T_RPAREN);
					goto out_wlp;
				}
				case fTKnd::T_RPAREN_E: {
					h.next();
					continue;
				}
				case fTKnd::T_ID_E :T_VAL_E: case fTKnd::T_VAR_E: case fTKnd::T_PROTECTED_E: case fTKnd::T_PRIVATE_E: case fTKnd::T_OVERRIDE_E:{
					cpcs->addParams(classParamClause());
					h.accept(fTKnd::T_RPAREN);
					continue;
				}
				default:
					throw std::runtime_error("Expected 'implicit' or ')' or class parameter but found: " + h.getToken()->toString());
			}
		}
		out_wlp:
	}

	sp<fClassParamClauses> fParser::classParamClauses() {
		sp<fClassParamClauses> cpcs = ms<fClassParamClauses>();
		classParamClauses2(cpcs);
		if (cpcs->getImplicitParams().empty() && cpcs->getClassParams().empty()) {
			return nullptr;
		}
		return cpcs;
	}

	std::vector<sp<fClassParam>> fParser::classParamClause() {
		std::vector<sp<fClassParam>> params;
		int sz = h.pushNLEnabled(false);
		while (true) {
			params.push_back(classParam());
			if (h.isTkComma()) {
				h.next();
				continue;
			}
			break;
		}
		h.popNLEnabled(sz, false);
		return params;
	}

	sp<fParamType> fParser::paramType(bool isSimpleType) {
		bool isFatArrow = false;
		bool isStar = false;
		if (!isSimpleType) {
			if (h.isLa(0, fTKnd::T_FAT_ARROW)) {
				isFatArrow = true;
				h.next();
			}
		}
		sp<fType> t = type();
		if (!isSimpleType) {
			if (h.getTokenKind() == fTKnd::T_STAR) {
				isStar = true;
				h.next();
			}
		}
		return ms<fParamType>(std::move(t), isFatArrow, isStar);
	}

	sp<fClassParam> fParser::classParam() {
		sp<fClassParam> p = ms<fClassParam>();
		p->setModifiers(modifiers());

		switch (*h.tKnd()) {
			case fTKnd::T_VAL_E: {
				p->setMutability(fVariableMutabilityTypeE::VAL);
				h.next();
				break;
			}
			case fTKnd::T_VAR_E: {
				p->setMutability(fVariableMutabilityTypeE::VAR);
				h.next();
				break;
			}
			default:
				p->setMutability(fVariableMutabilityTypeE::NONE);
				break;
		}

		p->setIdentifier(h.accept(fTKnd::T_ID));
		if (h.isTkColon()) {
			h.accept(fTKnd::T_COLON);
			p->setParamType(paramType(false));
		}
		if (h.isTkAssign()) {
			h.next();
			p->setDefaultValueExpr(expr(nullptr));
		}
		return p;
	}

	sp<fClassParents> fParser::classParents(bool isTrait) {
		sp<fClassParents> parents = ms<fClassParents>();
		parents->setConstr(classConstr(isTrait));
		while (h.isTkWith()) {
			h.next();
			parents->setWithType(simpleType());
		}
		return parents;
	}

	sp<fClassConstr> fParser::classConstr(bool isTrait) {
		sp<fClassConstr> cc = ms<fClassConstr>(simpleType());
		if (!isTrait && h.isTkLParen()) {
			cc->setArgsExpr(exprs());
		}
		return cc;
	}

	sp<fTypeParam> fParser::typeParam() {
		return typeParam2(ms<fTypeParam>());
	}

	sp<fTypeParam> fParser::typeParam2(sp<fTypeParam> p) {

		p->setTypeParamName(h.acceptOneOf({fTKnd::T_ID, fTKnd::T_UNDERSCORE}));
		if (h.isTkLBracket()) {
			p->setVariantTypeParams(variantTypeParams());
		}
		if (h.isTkLowerBound()) {
			h.next();
			p->setLowerBound(type());
		}
		if (h.isTkUpperBound()) {
			h.next();
			p->setUpperBound(type());
		}
		while (h.isTkContextBound()) {
			h.next();
			p->addContextBound(type());
		}
		while(h.isTkColon()) {
			h.next();
			p->addType(type());
		}

		return p;
	}

	sp<fVariantTypeParam> fParser::variantTypeParam() {
		fVarianceE variance = fVarianceE::INVARIANT;
		if (h.isTkPlus()) {
			h.next();
			variance = fVarianceE::COVARIANT;
		} else if (h.isTkMinus()) {
			h.next();
			variance = fVarianceE::CONTRAVARIANT;
		}
		sp<fVariantTypeParam> p = ms<fVariantTypeParam>(variance);
		typeParam2(std::dynamic_pointer_cast<fTypeParam>(p));
		return p;
	}

	std::vector<sp<fVariantTypeParam>> fParser::variantTypeParams() {
		std::vector<sp<fVariantTypeParam>> params;
		h.accept(fTKnd::T_LBRACKET);
		while (true) {
			params.push_back(variantTypeParam());
			if (h.isTkComma()) {
				h.next();
				continue;
			}
			break;
		}
		h.accept(fTKnd::T_RBRACKET);
		return params;
	}

	sp<fTemplate> fParser::classExtends(bool isTrait) {
		switch (*h.tKnd()) {
			case fTKnd::T_NL_E: {
				if (!h.isLa(1, fTKnd::T_LCURL)) {
					return nullptr;
				}
				// fall through
			}
			case fTKnd::T_LCURL_E: {
				return ms<fTemplate>(templateBody(), false);
			}
			case fTKnd::T_EXTENDS_E: {
				h.next();
				switch (*h.tKnd()) {
					case fTKnd::T_ID_E: case fTKnd::T_THIS_E: case fTKnd::T_SUPER_E: case fTKnd::T_LPAREN_E: {
						return classTemplate(true, isTrait);
					}
					case fTKnd::T_NL_E: {
						if (!h.isLa(1, fTKnd::T_LCURL)) {
							return nullptr;
						}
						// fall through
					}
					case fTKnd::T_LCURL_E: {
						return ms<fTemplate>(templateBody(), true);
					}
					default:
						throw std::runtime_error("Expected class template or '{' after 'extends' but found: " + h.getToken()->toString());
				}
			}
			default:
				break;
		}
		return nullptr;
	}


	sp<fTraitDef> fParser::traitDef(sp<fModifiers> mods) {
		h.accept(fTKnd::T_TRAIT);
		sp<fTraitDef> trait = ms<fTraitDef>(h.next(), std::move(mods));
		if (h.isTkLBracket()) {
			trait->setTypeParams(variantTypeParams());
		}
		trait->setExtendsTemplate(classExtends(true));
		return trait;
	}

	std::vector<const fToken*> fParser::qualIds() {
		std::vector<const fToken*> idTokens;
		while (true) {
			idTokens.push_back(h.accept(fTKnd::T_ID));
			if (h.isTkDot()) {
				h.next(); continue;
			}
			break;
		}
		return idTokens;
	}

	sp<fPackage> fParser::packageClause() {
		h.accept(fTKnd::T_PACKAGE);
		return ms<fPackage>(qualIds());
	}

	sp<vector<sp<fImportSelector>>> fParser::ImportSelectors() {

		h.accept(fTKnd::T_LCURL);
		sp<std::vector<sp<fImportSelector>>> selectors = ms<std::vector<sp<fImportSelector>>>();
		while (true) {
			const fToken* from = h.accept(fTKnd::T_ID);
			const fToken* to =from;
			if (h.isTkFatArrow()) {
				h.next();
				to = h.accept(fTKnd::T_ID);
			}
			selectors->push_back(ms<fImportSelector>(from, to));
			if (h.isTkComma()) {
				h.next(); continue;
			}
			break;
		}
		h.accept(fTKnd::T_RCURL);
		return selectors;
	}

	sp<fImport> fParser::importClause() {
		h.accept(fTKnd::T_IMPORT);
		auto imp = ms<fImport>();
		while (true) {
			sp<fImportExpr> ie = ms<fImportExpr>(stableId(false));
			if (h.isTkDot()) {
				h.next();
				switch (*h.tKnd()) {
					case fTKnd::T_UNDERSCORE_E:
						ie->setUnderscore(h.next());
						break;
					case fTKnd::T_LCURL_E: {
						ie->setSelectors(ImportSelectors());
						break;
					}
					default:
						throw std::runtime_error("Unexpected case");
				}
			}
			imp->addImportExpr(std::move(ie));
			if (h.isTkComma()) {
				h.next();
			} else {
				break;
			}
		}
		return imp;
	}

	sp<fLocalModifier> fParser::localModifier() {
		switch (*h.tKnd()) {
			case fTKnd::T_ABSTRACT_E:
				h.next();
				return ms<fLocalModifier>(fLangModifierTypeE::ABSTRACT);
			case fTKnd::T_FINAL_E:
				h.next();
				return ms<fLocalModifier>(fLangModifierTypeE::FINAL);
			case fTKnd::T_SEALED_E:
				h.next();
				return ms<fLocalModifier>(fLangModifierTypeE::SEALED);
			case fTKnd::T_IMPLICIT_E:
				h.next();
				return ms<fLocalModifier>(fLangModifierTypeE::IMPLICIT);
			case fTKnd::T_LAZY_E:
				h.next();
				return ms<fLocalModifier>(fLangModifierTypeE::LAZY);
			default:
				throw std::runtime_error("Unexpected local modifier: " + h.getToken()->toString());
		}
	}

	sp<fAccessModifier> fParser::accessModifier() {
		sp<fAccessModifier> am;
		switch (*h.tKnd()) {
			case fTKnd::T_PRIVATE_E:
				h.next();
				am = ms<fAccessModifier>(fLangModifierTypeE::PRIVATE);
				break;
			case fTKnd::T_PROTECTED_E:
				h.next();
				am = ms<fAccessModifier>(fLangModifierTypeE::PROTECTED);
				break;
			default:
				throw std::runtime_error("Unexpected access modifier: " + h.getToken()->toString());
		}

		if (h.isLa(0, fTKnd::T_LBRACKET)) {
			int sz = h.pushNLEnabled(false);
			h.accept(fTKnd::T_LBRACKET);
			switch (*h.tKnd()) {
				case fTKnd::T_ID_E:
					am->setQualifier(ms<fAccessQualifier>(fAccessQualifierE::ID, h.accept(fTKnd::T_ID)));
					break;
				case fTKnd::T_THIS_E:
					am->setQualifier(ms<fAccessQualifier>(fAccessQualifierE::THIS, h.accept(fTKnd::T_THIS)));
					break;
				default:
					throw std::runtime_error("Unexpected token in access modifier qualifier: " + h.getToken()->toString());
			}
			h.popNLEnabled(sz, false);
			h.accept(fTKnd::T_RBRACKET);
		}
		assert(am != nullptr);
		return am;
	}

	sp<fModifiers> fParser::modifiers() {
		sp<fModifiers> mods = nullptr;

		while (true) {
			switch (*h.tKnd()) {
				case fTKnd::T_ABSTRACT_E: case fTKnd::T_FINAL_E: case fTKnd::T_SEALED_E: case fTKnd::T_IMPLICIT_E: case fTKnd::T_LAZY_E: {
					if (mods == nullptr) {
						mods = ms<fModifiers>();
					}
					mods->addLocalModifier(localModifier());
					continue;
				}
				case fTKnd::T_PRIVATE_E: case fTKnd::T_PROTECTED_E: {
					if (mods == nullptr) {
						mods = ms<fModifiers>();
					} else {
						assert(mods->getAccessModifier() == nullptr && "Multiple access modifiers are not allowed");
					}
					mods->setAccessModifier(accessModifier());
					continue;
				}
				case fTKnd::T_OVERRIDE_E: {
					if (mods == nullptr) {
						mods = ms<fModifiers>();
					} else {
						assert(mods->getOverrideModifier() == nullptr && "Multiple override modifiers are not allowed");
					}
					mods->setOverrideModifier(ms<fOverrideModifier>()); h.next();
					continue;
				}
				default:
					goto out_wlp;
			}
		}
		out_wlp:
		return mods;
	}


	sp<fAstOprndNod> fParser::classObjectDef(bool isCase, sp<fModifiers> mods) {
		switch (*h.tKnd()) {
			case fTKnd::T_CLASS_E: {
				return classDef(isCase, mods);
			}
			case fTKnd::T_OBJECT_E: {
				return objectDef(isCase, mods);
			}
			default:
				throw std::runtime_error("Expected 'class' or 'object' but found: " + h.getToken()->toString());
		}
	}

	sp<fAstOprndNod> fParser::tmplDef(sp<fModifiers> mods) {
		bool isCase = false;
		switch (*h.tKnd()) {
			case fTKnd::T_CASE_E: {
				isCase = true; h.next();
				switch (*h.tKnd()) {
					case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E: {
						break;
					}
					default:
						throw std::runtime_error("'case' must precede 'class' or 'object': " + h.getToken()->toString());
				}
				case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E:{
					return classObjectDef(isCase, mods);
				}
				case fTKnd::T_TRAIT_E: {
					return traitDef(mods);
				}
				default:
					throw std::runtime_error("Expected '[case] class', '[case] object' or 'trait' but found: " + h.getToken()->toString());
			}
		}
	}

	sp<fCompileUnit> fParser::compileUnit() {
		auto cu = std::make_shared<fCompileUnit>();
		while(h.isTkPackage()) {
			cu->addPackage(packageClause());
			h.skipSemi();
		}

		while (true) {
			if (h.isTkImport()) {
				cu->addImport(importClause());
			} else {

				sp<fModifiers> mods = modifiers();
				switch (*h.tKnd()) {
					case fTKnd::T_CASE_E: case fTKnd::T_CLASS_E: case fTKnd::T_OBJECT_E: case fTKnd::T_TRAIT_E: {
						cu->addStmt(tmplDef(mods));
						break;
					}
					case fTKnd::T_EOF_E:
						goto out_while;
					default:
						throw std::runtime_error("Unexpected token in compilation unit: " + h.getToken()->toString());
				}
			}
			h.skipSemi();
		}
		out_while:
		return cu;
	}
}
