#pragma once


#include <string>

namespace zebra::lex {


	class fReader {
	private:
		char* buf_;
		int bix_;
		int unicodeConvBix_;
		int blen_;
		char chr_;
		char* strbuf_;
		int strBufCap_;
		int strBix_;

	public:

		void setSp(int newSp);
		int bp() const;
		int bufLen() const;
		char ch() const;
		int sp() const;

		std::string tokStrValue() const {
			return std::string(strbuf_, strBix_);
		}


		fReader(const std::string_view& input);

		void scanChar();

		void putChar(char c, bool scan);

		void putChar(char c);

		void putChar(bool scan);

		int digit(int base) const;

		char peekChar() const;

		bool isUnicode() const;

		void skipChar();

		void convertUnicode();

		~fReader() {
			if (buf_ != nullptr) delete [] buf_;
			if (strbuf_ != nullptr) delete [] strbuf_;
		}
	};
}
