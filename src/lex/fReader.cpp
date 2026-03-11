#include "lex/fReader.hpp"

#include <cstring>
#include <stdexcept>

#include "lex/util/fUtil.hpp"

namespace zebra::lex {

	using namespace zebra::lex::util;

	fReader::fReader(const std::string_view& input)
		: bix_(-1), unicodeConvBix_(-1), strBix_(0), strBufCap_(128) {

		if (input.size() > 0 && std::isspace(input[input.size() - 1])) {
			blen_ = input.size() - 1;
		} else {
			blen_ = input.size();
		}

		buf_ = new char[blen_ + 1];
		std::memcpy(buf_,  input.data(), blen_);
		buf_[blen_] = EOI;

		strbuf_ = new char[strBufCap_];

		scanChar();
	}


	void fReader::scanChar() {
		if (bix_ < blen_) {
			chr_ = buf_[++bix_];
			if (chr_ == '\\') {
				convertUnicode();
			}
		}
	}

	void fReader::putChar(char c, bool scan) {
		if (strBix_ >= strBufCap_) {
			strBufCap_ *= 2;
			strbuf_ = ensureCapacity(strbuf_, strBix_, strBufCap_);
		}

		strbuf_[strBix_++] = c;
		if (scan) {
			scanChar();
		}
	}

	void fReader::putChar(char c) {
		putChar(c, false);
	}

	void fReader::putChar(bool scan) {
		putChar(chr_, scan);
	}

	int fReader::digit(int base) const {
		const char c = chr_;
		if ('0' <= c && c <= '9') {
			if (base == 10) {
				return c - '0';
			}
			int val = c - '0';
			return (val < base) ? val : -1;
		}
		if (base == 16) {
			if ('a' <= c && c <= 'f') {
				return c - 'a' + 10;
			}
			if ('A' <= c && c <= 'F') {
				return c - 'A' + 10;
			}
		}
		return -1;
	}

	char fReader::peekChar() const {
		return (bix_ + 1 < blen_) ? buf_[bix_ + 1] : EOI;
	}

	bool fReader::isUnicode() const {
		return unicodeConvBix_ == bix_;
	}

	void fReader::skipChar() {
		bix_++;
	}

	void fReader::convertUnicode() {
		if (chr_ == '\\' && unicodeConvBix_ != bix_) {
			bix_++;
			chr_ = buf_[bix_];
			if (chr_ == 'u') {
				do {
					bix_++;
					chr_ = buf_[bix_];
				} while (chr_ == 'u');

				int limit = bix_ + 3;
				if (limit < blen_) {
					int d = digit(16);
					int code = d;
					while (bix_ < limit && d >= 0) {
						bix_++;
						chr_ = buf_[bix_];
						d = digit(16);
						code = (code << 4) + d;
					}
					if (d >= 0) {
						chr_ = static_cast<char>(code);
						unicodeConvBix_ = bix_;
						return;
					}
				}
				throw std::runtime_error("illegal.unicode.esc");
			} else {
				bix_--;
				chr_ = '\\';
			}
		}
	}


	int fReader::bp() const { return bix_; }
	int fReader::bufLen() const { return blen_; }
	char fReader::ch() const { return chr_; }
	int fReader::sp() const { return strBix_; }
	void fReader::setSp(int newSp) { strBix_ = newSp; }
}
