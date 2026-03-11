
#pragma once

#include <vector>
#include <cassert>

#include "fTokzr.hpp"
#include "fLexerIFace.hpp"
#include "kind/fTKnd.hpp"
#include "token/fToken.hpp"


namespace zebra::lex {


class fLexerImpl : public fLexerIFace {
private:
    fTokzr& _tokenizer;
    std::vector<const fToken*> _tokens;
    int _currIndex;
    int _eofIndex;

public:
    explicit fLexerImpl(fTokzr& tokenizer)
        : _tokenizer(tokenizer),
          _currIndex(-1),
          _eofIndex(-1) {

        _tokens.reserve(256);  // Initial capacity
        scanToken();
    }

    ~fLexerImpl() override = default;

    bool currentAtEof() const override {
        return _eofIndex > -1 && _currIndex >= _eofIndex;
    }

    bool filledToEof() const override {
        return _eofIndex > -1;
    }

    const fToken* nextToken() override {
        if (currentAtEof()) {
            return _tokens[_eofIndex];
        }

        if (++_currIndex < static_cast<int>(_tokens.size())) {
            return _tokens[_currIndex];
        }

        scanToken();
        return _tokens[_currIndex];
    }

    const fToken* lookAhead(int n) override {
        ensureLookahead(n);

        if (_eofIndex > -1 && _currIndex + n >= _eofIndex) {
            return _tokens[_eofIndex];
        }

        return _tokens[_currIndex + n];
    }

private:
    void scanToken() {
        if (filledToEof()) {
            return;
        }

        const fToken* token = _tokenizer.readToken();
        _tokens.push_back(token);
        int lastIx = static_cast<int>(_tokens.size()) - 1;

        // Check if we've reached EOF token
        if (token->getTKind() == fTKnd::T_EOF) {
            _eofIndex = lastIx;
        }
    }

    void ensureLookahead(int n) {
        assert(n >= 0);
        int ensureSize = _currIndex + 1 + n;

        while (static_cast<int>(_tokens.size()) < ensureSize) {
            if (filledToEof()) {
                return;
            }
            scanToken();
        }
    }
};

} // namespace flint::compiler::frontend::lex