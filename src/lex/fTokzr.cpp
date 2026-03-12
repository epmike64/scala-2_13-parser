
#include "lex/fTokzr.hpp"
#include "../../include/lex/util/fUtil.hpp"
#include "lex/token/fNumToken.hpp"

namespace zebra::lex {

    using namespace zebra::lex::kind;
    using namespace zebra::lex::util;

    const fToken* fTokzr::readToken() {
        reader_.setSp(0);
        tokStrVal_.clear();
        radix_ = 0;

        tKnd_ = nullptr;
        int pos_ = 0;
        int endPos_ = 0;

        while (true) {
            assert(reader_.sp() == 0 && tokStrVal_.empty() && radix_ == 0);
            pos_ = reader_.bp();

            switch (reader_.ch()) {
                case EOI: {
                    tKnd_ = fTKnd::T_EOF;
                    goto exit_loop;
                }
                case SP: case TAB: case FF: {
                    do {
                        reader_.scanChar();
                    } while (reader_.ch() == SP || reader_.ch() == TAB || reader_.ch() == FF);
                    continue;
                }
                case CR: {
                    reader_.scanChar();
                    continue;
                }
                case LF: {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_NL;
                    goto exit_loop;
                }
                case 's': {
                    if (reader_.peekChar() == '"') {
                        reader_.scanChar();
                        scanLiteralString();
                        goto exit_loop;
                    }
                    [[fallthrough]];
                }
                case 'A': case 'B': case 'C': case 'D': case 'E':
                case 'F': case 'G': case 'H': case 'I': case 'J':
                case 'K': case 'L': case 'M': case 'N': case 'O':
                case 'P': case 'Q': case 'R': case 'S': case 'T':
                case 'U': case 'V': case 'W': case 'X': case 'Y':
                case 'Z':
                case 'a': case 'b': case 'c': case 'd': case 'e':
                case 'f': case 'g': case 'h': case 'i': case 'j':
                case 'k': case 'l': case 'm': case 'n': case 'o':
                case 'p': case 'q': case 'r': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y':
                case 'z':
                case '$': case '_': {
                    scanIdent(pos_);
                    goto exit_loop;
                }
                case '0': {
                    reader_.scanChar();
                    if (reader_.ch() == 'x' || reader_.ch() == 'X') {
                        reader_.scanChar();
                        scanNumber(pos_, 16);
                    } else if (reader_.ch() == 'b' || reader_.ch() == 'B') {
                        reader_.scanChar();
                        scanNumber(pos_, 2);
                    } else {
                        reader_.putChar('0');
                        scanNumber(pos_, 8);
                    }
                    goto exit_loop;
                }
                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9': {
                    scanNumber(pos_, 10);
                    goto exit_loop;
                }
                case '.': {
                    reader_.scanChar();
                    if (reader_.digit(10) >= 0) {
                        reader_.putChar('.');
                        scanFractionAndSuffix(pos_);
                    } else {
                        tKnd_ = fTKnd::T_DOT;
                    }
                    goto exit_loop;
                }
                case ',': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_COMMA;
                    goto exit_loop;
                }
                case ';': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_SEMICOLON;
                    goto exit_loop;
                }
                case '(': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_LPAREN;
                    goto exit_loop;
                }
                case ')': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_RPAREN;
                    goto exit_loop;
                }
                case '[': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_LBRACKET;
                    goto exit_loop;
                }
                case ']': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_RBRACKET;
                    goto exit_loop;
                }
                case '{': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_LCURL;
                    goto exit_loop;
                }
                case '}': {
                    reader_.scanChar();
                    tKnd_ = fTKnd::T_RCURL;
                    goto exit_loop;
                }
                case '/': {
                    if (reader_.peekChar() == '/') {
                        // Single line comment
                        do {
                            reader_.scanChar();
                        } while (reader_.ch() != CR && reader_.ch() != LF && reader_.bp() < reader_.bufLen());
                        continue;
                    }

                    if (reader_.peekChar() == '*') {
                        // Multi-line comment
                        reader_.skipChar();
                        reader_.scanChar();
                        while (reader_.bp() < reader_.bufLen()) {
                            if (reader_.ch() == '*') {
                                reader_.scanChar();
                                if (reader_.ch() == '/') break;
                            } else {
                                reader_.scanChar();
                            }
                        }
                        if (reader_.ch() == '/') {
                            reader_.scanChar();
                            continue;
                        }
                        lexError(pos_, "unclosed.comment");
                    }

                    scanIdent(pos_);
                    goto exit_loop;
                }
                case '\'': {
                    reader_.scanChar();
                    if (reader_.ch() == '\'') {
                        lexError(pos_, "empty.char.lit");
                        reader_.scanChar();
                    } else {
                        if (reader_.ch() == CR || reader_.ch() == LF)
                            lexError(pos_, "illegal.line.end.in.char.lit");
                        scanLitChar();
                        if (reader_.ch() == '\'') {
                            reader_.scanChar();
                            tKnd_ = fTKnd::T_CHAR_LIT;
                        } else {
                            lexError(pos_, "unclosed.char.lit");
                        }
                    }
                    goto exit_loop;
                }
                case '"': {
                    scanLiteralString();
                    goto exit_loop;
                }
                default: {
                    if (isOpChar(reader_.ch())) {
                        scanIdent(pos_);
                        goto exit_loop;
                    }
                    throw std::runtime_error("illegal.char");
                }
            }
        }

        exit_loop:
        endPos_ = reader_.bp();


        switch (tKnd_->getTTag()) {
            case fTTagE::OPERATOR:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, fToken::OPERATOR));
            case fTTagE::KEYWORD:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, fToken::KEYWORD));
            case fTTagE::INTERN:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, fToken::INTERN));
            case fTTagE::NAME_VAL:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, tokStrVal_));
            case fTTagE::STRING:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, tokStrVal_));
            case fTTagE::NUMERIC:
                return tokBuf_.addToken(fNumToken(tKnd_, pos_, endPos_, tokStrVal_, radix_));
            case fTTagE::UNDERSCORE:
                return tokBuf_.addToken(fToken(tKnd_, pos_, endPos_, tokStrVal_));
            default:
                throw std::runtime_error("Unknown token tag");
        }
    }


    void fTokzr::scanLiteralString() {
        assert(reader_.ch() == '"');
        reader_.scanChar();
        while (reader_.ch() != '"' && reader_.ch() != CR && reader_.ch() != LF && reader_.bp() < reader_.bufLen()) {
            scanLitChar();
        }
        if (reader_.ch() == '"') {
            tKnd_ = fTKnd::T_STRING_LIT;
            reader_.scanChar();
            tokStrVal_ = reader_.tokStrValue();
        } else {
            lexError(-1, "unclosed.str.lit");
        }
    }

    void fTokzr::scanLitChar() {
        if (reader_.ch() == '\\') {
            if (reader_.peekChar() == '\\' && !reader_.isUnicode()) {
                reader_.skipChar();
                reader_.putChar('\\', true);
            } else {
                reader_.scanChar();
                switch (reader_.ch()) {
                    case '0': case '1': case '2': case '3':
                    case '4': case '5': case '6': case '7': {
                        char leadch = reader_.ch();
                        int oct = reader_.digit(8);
                        reader_.scanChar();
                        if ('0' <= reader_.ch() && reader_.ch() <= '7') {
                            oct = oct * 8 + reader_.digit(8);
                            reader_.scanChar();
                            if (leadch <= '3' && '0' <= reader_.ch() && reader_.ch() <= '7') {
                                oct = oct * 8 + reader_.digit(8);
                                reader_.scanChar();
                            }
                        }
                        reader_.putChar(static_cast<char>(oct));
                        break;
                    }
                    case 'b': reader_.putChar('\b', true); break;
                    case 't': reader_.putChar('\t', true); break;
                    case 'n': reader_.putChar('\n', true); break;
                    case 'f': reader_.putChar('\f', true); break;
                    case 'r': reader_.putChar('\r', true); break;
                    case '\'': reader_.putChar('\'', true); break;
                    case '"': reader_.putChar('"', true); break;
                    case '\\': reader_.putChar('\\', true); break;
                    default:
                        lexError(reader_.bp(), "illegal.esc.char");
                }
            }
        } else if (reader_.bp() != reader_.bufLen()) {
            reader_.putChar(true);
        }
    }

    bool fTokzr::isOpChar(char ch) const {
        switch (ch) {
            case '!': case '#': case '%': case '&': case '*': case '+': case '-': case '/': case ':':
            case '<': case '=': case '>': case '?': case '@': case '\\': case '^': case '|': case '~':
                return true;
            default:
                return false;
        }
    }

    void fTokzr::scanIdent(int pos) {
        bool seenOpChar = false;
        if (isOpChar(reader_.ch())) {
            seenOpChar = true;
        }

        while (true) {
            char prev = reader_.ch();
            reader_.putChar(true);

            switch (reader_.ch()) {
                case 'A': case 'B': case 'C': case 'D': case 'E':
                case 'F': case 'G': case 'H': case 'I': case 'J':
                case 'K': case 'L': case 'M': case 'N': case 'O':
                case 'P': case 'Q': case 'R': case 'S': case 'T':
                case 'U': case 'V': case 'W': case 'X': case 'Y':
                case 'Z': case '$':
                case 'a': case 'b': case 'c': case 'd': case 'e':
                case 'f': case 'g': case 'h': case 'i': case 'j':
                case 'k': case 'l': case 'm': case 'n': case 'o':
                case 'p': case 'q': case 'r': case 's': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y':
                case 'z': case '_':
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    if (seenOpChar) {
                        goto exit_ident_loop;
                    }
                    continue;

                default:
                    if (isOpChar(reader_.ch())) {
                        if (prev == '_') {
                            seenOpChar = true;
                            continue;
                        } else if (seenOpChar) {
                            continue;
                        }
                    }
                    goto exit_ident_loop;
            }
        }

        exit_ident_loop:
        tokStrVal_ = reader_.tokStrValue();
        tKnd_ = fTKnd::findByName(tokStrVal_);
    }

    void fTokzr::scanDigits(int pos, int digitRadix) const {
        do {
            reader_.putChar(true);
        } while (reader_.digit(digitRadix) >= 0);
    }

    void fTokzr::scanHexExponentAndSuffix(int pos) {
        if (reader_.ch() == 'p' || reader_.ch() == 'P') {
            reader_.putChar(true);

            if (reader_.ch() == '+' || reader_.ch() == '-') {
                reader_.putChar(true);
            }

            if (reader_.digit(10) >= 0) {
                scanDigits(pos, 10);
                lexError(pos, "unsupported.cross.fp.lit");
            } else {
                lexError(pos, "malformed.fp.lit");
            }
        } else {
            lexError(pos, "malformed.fp.lit");
        }

        if (reader_.ch() == 'f' || reader_.ch() == 'F') {
            reader_.putChar(true);
            tKnd_ = fTKnd::T_FLOAT_LIT;
            radix_ = 16;
        } else {
            if (reader_.ch() == 'd' || reader_.ch() == 'D') {
                reader_.putChar(true);
            }
            tKnd_ = fTKnd::T_FLOAT_LIT;
            radix_ = 16;
        }
    }

    void fTokzr::scanFraction(int pos) {
        if (reader_.digit(10) >= 0) {
            scanDigits(pos, 10);
        }
        int sp1 = reader_.sp();
        if (reader_.ch() == 'e' || reader_.ch() == 'E') {
            reader_.putChar(true);

            if (reader_.ch() == '+' || reader_.ch() == '-') {
                reader_.putChar(true);
            }

            if (reader_.digit(10) >= 0) {
                scanDigits(pos, 10);
                return;
            }
            lexError(pos, "malformed.fp.lit");
            reader_.setSp(sp1);
        }
    }

    void fTokzr::scanFractionAndSuffix(int pos) {
        radix_ = 10;
        scanFraction(pos);
        if (reader_.ch() == 'f' || reader_.ch() == 'F') {
            reader_.putChar(true);
            tKnd_ = fTKnd::T_FLOAT_LIT;
        } else {
            if (reader_.ch() == 'd' || reader_.ch() == 'D') {
                reader_.putChar(true);
            }
            tKnd_ = fTKnd::T_FLOAT_LIT;
        }
    }

    void fTokzr::scanHexFractionAndSuffix(int pos, bool seendigit) {
        radix_ = 16;
        assert(reader_.ch() == '.');
        reader_.putChar(true);

        if (reader_.digit(16) >= 0) {
            seendigit = true;
            scanDigits(pos, 16);
        }
        if (!seendigit) {
            lexError(pos, "invalid.hex.number");
        } else {
            scanHexExponentAndSuffix(pos);
        }
    }

    void fTokzr::scanNumber(int pos, int radix) {
        radix = radix;
        int digitRadix = (radix == 8 ? 10 : radix);
        int firstDigit = reader_.digit(std::max(10, digitRadix));
        bool seendigit = firstDigit >= 0;
        bool seenValidDigit = firstDigit >= 0 && firstDigit < digitRadix;

        if (seendigit) {
            scanDigits(pos, digitRadix);
        }

        if (seendigit && radix == 16 && (reader_.ch() == 'p' || reader_.ch() == 'P')) {
            scanHexExponentAndSuffix(pos);
        } else if (digitRadix == 10 && reader_.ch() == '.') {
            char p = reader_.peekChar();
            if ('0' <= p && p <= '9') {
                reader_.putChar(true);
                scanFractionAndSuffix(pos);
            } else {
                tokStrVal_ = reader_.tokStrValue();
                tKnd_ = fTKnd::T_INT_LIT;
            }
        } else if (digitRadix == 10 &&
                   (reader_.ch() == 'e' || reader_.ch() == 'E' ||
                    reader_.ch() == 'f' || reader_.ch() == 'F' ||
                    reader_.ch() == 'd' || reader_.ch() == 'D')) {
            scanFractionAndSuffix(pos);
                    } else {
                        if (!seenValidDigit) {
                            switch (radix) {
                                case 2:
                                    lexError(pos, "invalid.binary.number");
                                    break;
                                case 16:
                                    lexError(pos, "invalid.hex.number");
                                    break;
                            }
                        }
                        tokStrVal_ = reader_.tokStrValue();
                        if (reader_.ch() == 'l' || reader_.ch() == 'L') {
                            reader_.scanChar();
                            tKnd_ = fTKnd::T_INT_LIT;
                        } else {
                            tKnd_ = fTKnd::T_INT_LIT;
                        }
                    }
    }

    void fTokzr::lexError(int pos, const std::string& key) {
        tKnd_ = fTKnd::T_ERROR;
        _errPos = pos;
        throw std::runtime_error("pos: " + std::to_string(pos) + ", key=" + key);
    }
}
