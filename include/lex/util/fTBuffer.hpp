#pragma once

#include <vector>

#include "lex/kind/fLangOperatorKind.hpp"
#include "lex/token/fToken.hpp"

namespace zebra::lex::util {

	using fToken = token::fToken;

	class fTBuffer {
	private:
		std::vector<const fToken*> _tokens;
	public:
		explicit fTBuffer(size_t initialCapacity = 1024) {
			if (initialCapacity > 0) {
				_tokens.reserve(initialCapacity);
			}
		}

		~fTBuffer() {
			for (auto it = _tokens.begin(); it != _tokens.end(); ++it) {
				delete *it;
			}
		}

		const fToken* addToken(const fToken* token) {
			_tokens.push_back(token);
			return token;
		}

		const fToken* getToken(size_t index) const {
			if (index >= _tokens.size()) {
				throw std::out_of_range("Token index out of range");
			}
			return _tokens[index];
		}

		const fToken* operator[](size_t index) {
			if (index >= _tokens.size()) {
				throw std::out_of_range("Token index out of range");
			}
			return _tokens[index];
		}
	};
}
