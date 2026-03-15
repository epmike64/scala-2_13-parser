#pragma once

#include "ast/node/fAstNod.hpp"
#include "ast/node/fAstOptrNod.hpp"
#include "lex/fLexerIFace.hpp"
#include "lex/kind/fLangOperatorKind.hpp"
#include "lex/kind/fTKnd.hpp"
#include "lex/token/fToken.hpp"
#include "parse/fAst.hpp"
#include "util/fCommon.hpp"
#include <memory>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <initializer_list>

#include "lex/kind/fLangPseudoOperatorKindE.hpp"

namespace zebra::parse {

    using namespace lex::kind;
    using namespace lex::token;
    using namespace ast;

class fParseHelp {
private:
    lex::fLexerIFace& lexer_;
    const fToken* _prevToken;
    const fToken* token_;
    std::stack<bool> isNLEnabledStack_;
    int _nlCount = 0;
    int _tc = 0;

public:
    fParseHelp(lex::fLexerIFace& lexer);

    int pushNLEnabled(bool enabled) ;

    bool popNLEnabled(int sz, bool expectedTop) ;

    bool isNLEnabled() const ;


private:
    const fToken* firstNonNL(int from) ;


public:
    int getNLCount() const {
        return _nlCount;
    }

    const fToken* next() ;

    const fTKnd* getTokenKind() const ;

    // Token kind checking methods
    bool isTkColon() const { return token_->getTKind() == fTKnd::T_COLON; }
    bool isTkAssign() const { return token_->getTKind() == fTKnd::T_ASSIGN; }
    bool isTkPlus() const { return token_->getTKind() == fTKnd::T_PLUS; }
    bool isTkMinus() const { return token_->getTKind() == fTKnd::T_MINUS; }
    bool isTkPipe() const { return token_->getTKind() == fTKnd::T_PIPE; }
    bool isTkYield() const { return token_->getTKind() == fTKnd::T_YIELD; }
    bool isTkRCurl() const { return token_->getTKind() == fTKnd::T_RCURL; }
    bool isTkIf() const { return token_->getTKind() == fTKnd::T_IF; }
    bool isTkCatch() const { return token_->getTKind() == fTKnd::T_CATCH; }
    bool isTkFinally() const { return token_->getTKind() == fTKnd::T_FINALLY; }
    bool isTkStar() const { return token_->getTKind() == fTKnd::T_STAR; }
    bool isTkContextBound() const { return token_->getTKind() == fTKnd::T_CONTEXT_BOUND; }
    bool isTkLowerBound() const { return token_->getTKind() == fTKnd::T_LOWER_BOUND; }
    bool isTkUpperBound() const { return token_->getTKind() == fTKnd::T_UPPER_BOUND; }
    bool isTkLParen() const { return token_->getTKind() == fTKnd::T_LPAREN; }
    bool isTkRParen() const { return token_->getTKind() == fTKnd::T_RPAREN; }
    bool isTkImplicit() const { return token_->getTKind() == fTKnd::T_IMPLICIT; }
    bool isTkLBracket() const { return token_->getTKind() == fTKnd::T_LBRACKET; }
    bool isTkExtends() const { return token_->getTKind() == fTKnd::T_EXTENDS; }
    bool isTkLCurl() const { return token_->getTKind() == fTKnd::T_LCURL; }
    bool isTkCase() const { return token_->getTKind() == fTKnd::T_CASE; }
    bool isTkIF() const { return token_->getTKind() == fTKnd::T_IF; }
    bool isTkElse() const { return token_->getTKind() == fTKnd::T_ELSE; }
    bool isTkDot() const { return token_->getTKind() == fTKnd::T_DOT; }
    bool isTkId() const { return token_->getTKind() == fTKnd::T_ID; }
    bool isTkComma() const { return token_->getTKind() == fTKnd::T_COMMA; }
    bool isTkWith() const { return token_->getTKind() == fTKnd::T_WITH; }
    bool isTkFatArrow() const { return token_->getTKind() == fTKnd::T_FAT_ARROW; }
    bool isTkPackage() const { return token_->getTKind() == fTKnd::T_PACKAGE; }
    bool isTkTID() const { return token_->getTKind() == fTKnd::T_ID; }
    bool isTkTHIS() const { return token_->getTKind() == fTKnd::T_THIS; }
    bool isTkSemicolon() const { return token_->getTKind() == fTKnd::T_SEMICOLON; }
    bool isTkNL() const { return token_->getTKind() == fTKnd::T_NL; }
    bool isTkUnderscore() const { return token_->getTKind() == fTKnd::T_UNDERSCORE; }
    bool isTkImport() const { return token_->getTKind() == fTKnd::T_IMPORT; }

    const fToken* getToken() const;


    const fTKnd* tKnd() const;

    const fToken* acceptOneOf(std::initializer_list<const fTKnd*> types) ;

    const fToken* accept(const fTKnd* kind) ;

    const fToken* lookAhead(int n)  ;

    bool isLa(const int la, std::initializer_list<const fTKnd*> types) ;


    bool isLa(int la, const fTKnd* type) ;

   // const fLangOperatorKind* getOprKnd(const fToken* token) const ;


    void skipNL() ;


    void skipAllNLs();


    bool skipSemi() ;



    void expectOneOf(int la, std::initializer_list<const fTKnd*> types) ;

    void insertPseudoOperator(sp<fAst> a, fLangPseudoOperatorKindE k, const fToken *operatorToken);

    void insertMethodNameOperator(sp<fAst> a, const fToken *operatorToken);

    void insertIdOperator(sp<fAst> a, fLangPseudoOperatorKindE k, const fToken *operatorToken);


    void insertOperator(sp<fAst> a, const fLangOperatorKind* k, const fToken* operatorToken) ;

};

} // namespace com::flint::compiler::frontend::parse