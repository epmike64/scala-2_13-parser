#pragma once
#include <list>
#include <memory>
#include <vector>
#include <unordered_map>


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
	sp<T> dynSp(sp<U> basePtr);
}
