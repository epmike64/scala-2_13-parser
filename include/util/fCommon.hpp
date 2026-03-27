#pragma once
#include <list>
#include <vector>
#include <unordered_map>

#include "ast/symbol/ZSymbol.hpp"

namespace zebra::util {

	template<typename T, typename... Args>
	auto ms(Args &&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T >
	using sp = std::shared_ptr<T>;


	template<typename T>
	using PVecP = sp<std::vector<std::shared_ptr<T>>>;

	template<typename T>
	using PVec = sp<std::vector<T>>;

	template<typename T>
	using vecP = std::vector<std::shared_ptr<T>>;

	template<typename T >
	using StrPVecPMap = sp<std::unordered_map<std::string, PVecP<T>>>;

	template<typename T, typename U>
	sp<T> dynSp(sp<U> basePtr) {
		sp<T> res = std::dynamic_pointer_cast<T>(basePtr);
		if (!res) {
			throw std::runtime_error("Failed to cast pointer of type " + std::string(typeid(U).name()) +
			                         " to type " + std::string(typeid(T).name()));
		}
		return res;
	}
}
