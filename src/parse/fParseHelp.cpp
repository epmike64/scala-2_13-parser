#include "parse/fParseHelp.hpp"

#include "lex/kind/fLangPseudoOperatorKindE.hpp"
#include "util/fCommon.hpp"

namespace zebra::parse {

    using namespace lex::token;
    using namespace zebra::util;

	fParseHelp::fParseHelp(lex::fLexerIFace& lexer)
		: lexer_(lexer), token_(&fToken::FILE_OFFSET) {
		isNLEnabledStack_.push(true); // Default is NL enabled
		next();
	}

	int fParseHelp::pushNLEnabled(bool enabled) {
		isNLEnabledStack_.push(enabled);
		return static_cast<int>(isNLEnabledStack_.size());
	}

	bool fParseHelp::popNLEnabled(int sz, bool expectedTop) {
		assert(static_cast<int>(isNLEnabledStack_.size()) == sz && isNLEnabledStack_.top() == expectedTop);
		bool v = isNLEnabledStack_.top();
		isNLEnabledStack_.pop();
		if (isNLEnabledStack_.empty()) {
			throw std::runtime_error("NLStack is empty");
		}
		return v;
	}

	bool fParseHelp::isNLEnabled() const {
		return isNLEnabledStack_.top();
	}


	const fToken* fParseHelp::firstNonNL(int from) {
		for (int i = from; ; i++) {
			auto laToken = lookAhead(i);
			if (laToken->getTKind() != fTKnd::T_NL) {
				return laToken;
			}
		}
	}


    const fToken* fParseHelp::next() {
        _prevToken = token_;

        while (true) {
            _nlCount = 0;
            token_ = lexer_.nextToken();
            if (token_->getTKind() != fTKnd::T_NL) {
                break;
            }
            _nlCount++;
            while (isLa(1, fTKnd::T_NL)) {
                lexer_.nextToken();
                _nlCount++;
            }

            // 1. Test previous token to see if it can terminate a statement
            const fTKnd* prevKind = _prevToken->getTKind();
            if (prevKind == fTKnd::T_ID || prevKind == fTKnd::T_THIS ||
                prevKind == fTKnd::T_INT_LIT || prevKind == fTKnd::T_STRING_LIT ||
                prevKind == fTKnd::T_CHAR_LIT || prevKind == fTKnd::T_FLOAT_LIT ||
                prevKind == fTKnd::T_NULL || prevKind == fTKnd::T_TRUE ||
                prevKind == fTKnd::T_FALSE || prevKind == fTKnd::T_RETURN ||
                prevKind == fTKnd::T_TYPE || prevKind == fTKnd::T_UNDERSCORE ||
                prevKind == fTKnd::T_RPAREN || prevKind == fTKnd::T_RBRACKET ||
                prevKind == fTKnd::T_RCURL) {
                // Previous can terminate a statement
            } else {
                // Previous cannot terminate a statement, so continue
                continue; // NL is discarded
            }

            // 2. Test LookAhead token to see if it can start a statement
            auto la = lexer_.lookAhead(1);
            const fTKnd* laKind = la->getTKind();

            // Tokens that can NOT start a statement
            if (laKind == fTKnd::T_CATCH || laKind == fTKnd::T_ELSE ||
                laKind == fTKnd::T_EXTENDS || laKind == fTKnd::T_FINALLY ||
                laKind == fTKnd::T_MATCH || laKind == fTKnd::T_WITH ||
                laKind == fTKnd::T_YIELD || laKind == fTKnd::T_COMMA ||
                laKind == fTKnd::T_DOT || laKind == fTKnd::T_COLON ||
                laKind == fTKnd::T_ASSIGN || laKind == fTKnd::T_FAT_ARROW ||
                laKind == fTKnd::T_IN || laKind == fTKnd::T_UPPER_BOUND ||
                laKind == fTKnd::T_LOWER_BOUND || laKind == fTKnd::T_CONTEXT_BOUND ||
                laKind == fTKnd::T_POUND || laKind == fTKnd::T_LBRACKET ||
                laKind == fTKnd::T_RPAREN || laKind == fTKnd::T_RBRACKET ||
                laKind == fTKnd::T_RCURL) {
                continue; // NL is discarded
            }

            if (laKind == fTKnd::T_CASE) {
                auto f = firstNonNL(2);
                if (f->getTKind() != fTKnd::T_CLASS && f->getTKind() != fTKnd::T_OBJECT) {
                    continue; // NL is discarded
                }
            }

            if (isNLEnabled()) {
                break; // NL is returned
            }
        }

        std::cout << (_tc++) << " : " << token_->toString() << std::endl;
        return _prevToken;
    }

    const fTKnd* fParseHelp::getTokenKind() const {
        return token_->getTKind();
    }


    const fToken* fParseHelp::getToken() const {
        return token_;
    }

    const fTKnd* fParseHelp::tKnd() const {
        return token_->getTKind();
    }

    const fToken* fParseHelp::acceptOneOf(std::initializer_list<const fTKnd*> types) {
	    for (const auto& type : types) {
	        if (token_->getTKind() == type) {
	            return next();
	        }
	    }
        std::string expected;
        for (const auto& type : types) {
            if (!expected.empty()) expected += ", ";
            expected += type->toString();
        }
        throw std::runtime_error("Expected any of [" + expected + "] but found " + token_->getTKind()->toString());
    }

    const fToken* fParseHelp::accept(const fTKnd* kind) {
        if (token_->getTKind() != kind) {
            throw std::runtime_error("Expected " + kind->toString() + " but found " + token_->getTKind()->toString());
        }
        return next();
    }

    const fToken* fParseHelp::lookAhead(int n)  {
        return lexer_.lookAhead(n);
    }

    bool fParseHelp::isLa(int la, std::initializer_list<const fTKnd*> types) {
        const fToken* laToken = lookAhead(la);
        for (const auto& type : types) {
            if (laToken->getTKind() == type) {
                return true;
            }
        }
        return false;
    }

    bool fParseHelp::isLa(const int la, const fTKnd* type)  {
        auto laToken = lookAhead(la);
        return laToken->getTKind() == type;
    }

    // const fLangOperatorKind* fParseHelp::getOprKnd(const fToken* token) const {
    //     return fLangOperatorKind::getOptrKnd(token);
    // }

    void fParseHelp::skipNL() {
        if (isTkNL()) next();
    }

    void fParseHelp::skipAllNLs() {
        while (isTkNL()) next();
    }

    bool fParseHelp::skipSemi() {
        if (token_->getTKind() == fTKnd::T_SEMICOLON) {
            next();
            return true;
        } else if (token_->getTKind() == fTKnd::T_NL) {
            while (isTkNL()) next();
            return true;
        }
        return false;
    }

    void fParseHelp::expectOneOf(int la, std::initializer_list<const fTKnd*> types)  {
        assert(types.size() > 0);
       const fToken* laToken = lookAhead(la);
        for (const auto& type : types) {
            if (laToken->getTKind() == type) {
                return;
            }
        }
        throw std::runtime_error("Unexpected token: " + token_->getTKind()->toString());
    }


    void fParseHelp::insertPseudoOperator(sp<fAst> a, fLangPseudoOperatorKindE k, const fToken* operatorToken) {
	    insertOperator(a, fLangOperatorKind::O_PSEUDO, operatorToken);
	}

    void fParseHelp::insertOperator(sp<fAst> a, const fLangOperatorKind* k, const fToken* operatorToken) {
        std::shared_ptr<fAstNod> last = a->astLastN();
        assert(!last->isOperator() && "Last node should not be operator");

        std::shared_ptr<fAstNod> _prn = last->getAstParentN();
        assert(_prn && _prn->isOperator() && _prn->getAstRightN() == last);

	    std::shared_ptr<fAstOptrNod> prn = std::dynamic_pointer_cast<fAstOptrNod>(_prn);

         std::shared_ptr<fAstOptrNod> op =std::make_shared<fAstOptrNod>(k, operatorToken);

        if (prn == a->astRootOpr()) {
            a->astRootOpr()->setAstRightN(op);
            op->setAstLeftN(last);
        } else {
            if (k->precedence() > prn->getLangOptrKnd()->precedence() || k->isRightAssociative()) {
                auto right = prn->getAstRightN();
                assert(!right->isOperator());
                prn->setAstRightN(op);
                op->setAstLeftN(right);
            } else {
                sp<fAstNod> grandParent = prn->getAstParentN();
                assert(grandParent && grandParent->isOperator());
                grandParent->setAstRightN(op);
                op->setAstLeftN(prn);
            }
        }
        a->setAstLastN(op);
    }

}
