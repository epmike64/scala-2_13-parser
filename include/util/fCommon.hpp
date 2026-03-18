#pragma once
#include <list>
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
	using PtrVec = sp<std::vector<std::shared_ptr<T>>>;

	template<typename T >
	using StrVecMap = sp<std::unordered_map<std::string, PtrVec<T>>>;
}
