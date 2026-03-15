

#pragma once

#include <string>
#include "fReader.hpp"
#include "lex/kind/fTKnd.hpp"
#include "token/fToken.hpp"
#include "lex/util/fTBuffer.hpp"

namespace zebra::lex {

    using namespace  zebra::lex::kind;
    using namespace zebra::lex::token;
    using  zebra::lex::util::fTBuffer;

class fTokzr {
private:
    fReader& reader_;
    fTBuffer& tokBuf_;
    int radix_;
    std::string tokStrVal_;
    const fTKnd* tKnd_;  // Pointer to const fTokenKind
    int _errPos;

public:
    fTokzr(fReader& reader, fTBuffer& tokBuf)
        : reader_(reader), tokBuf_(tokBuf), radix_(0), tKnd_(nullptr), _errPos(-1) {}


   const fToken* readToken();

    void scanLiteralString();

    void scanStringFinish();

    void scanInterpLiteralString();

    void scanIdent(int pos);

    void scanLitChar();

    bool isOpChar(char ch) const;

    void scanDigits(int pos, int digitRadix) const;


    void scanHexExponentAndSuffix(int pos);


    void scanFraction(int pos);

    void scanFractionAndSuffix(int pos);


    void scanHexFractionAndSuffix(int pos, bool seendigit);


    void scanNumber(int pos, int radix);

    void lexError(int pos, const std::string& key);

};

}
