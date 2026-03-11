#pragma once

namespace zebra::util {

	template<typename T, typename... Args>
	auto ms(Args &&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T >
	using sp = std::shared_ptr<T>;
}