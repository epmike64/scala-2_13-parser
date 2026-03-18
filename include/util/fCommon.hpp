#pragma once
#include <vector>
#include <unordered_map>

namespace zebra::util {

	template<typename T, typename... Args>
	auto ms(Args &&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T >
	using sp = std::shared_ptr<T>;

	template<typename T >
	using StrListMap = std::unordered_map<std::string, sp<std::vector<sp<T>>>>;
}
