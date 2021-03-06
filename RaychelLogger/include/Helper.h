/*
 * Helper.h
 *
 *  Created on: 18.02.2021
 *      Author: weckyy
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <type_traits>
#include <functional>
#include <string_view>

namespace Logger {

	namespace details {

		template<size_t off_, typename = std::enable_if_t<(off_ < sizeof(uint32_t))>>
		constexpr uint32_t bit() {
			return 1ul << off_;
		}

		template<typename S, typename T, typename = void>
		struct is_to_stream_writable : std::false_type {};

		template<typename S, typename T>
		struct is_to_stream_writable<S, T,
			std::void_t<  decltype(std::declval<S&>() << std::declval<T>())  > >
			: std::true_type {};

		template<typename S, typename T>
		constexpr bool is_to_stream_writable_v = is_to_stream_writable<S, T>::value;

		template<typename T, typename = void>
		struct is_std_hashable : std::false_type {};

		template<typename T>
		struct is_std_hashable<T,
			std::void_t< decltype(std::declval<std::hash<T>>()(std::declval<T>()))> >
			: std::true_type {};

		template<typename T>
		constexpr bool is_std_hashable_v = is_std_hashable<T>::value;

		//thank you to einpoklum at https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
		template <typename T>
		constexpr std::string_view type_name()
		{
			std::string_view name, prefix, suffix;
#ifdef __clang__
			name = __PRETTY_FUNCTION__;
			prefix = "std::string_view Logger::details::type_name() [T = ";
			suffix = "]";
#elif defined(__GNUC__)
			name = __PRETTY_FUNCTION__;
			prefix = "constexpr std::string_view Logger::details::type_name() [with T = ";
			suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
			name = __FUNCSIG__;
			prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl Logger::details::type_name<";
			suffix = ">(void)";
#endif
			name.remove_prefix(prefix.size());
			name.remove_suffix(suffix.size());
			return name;
		}
	}
}


#endif /* HELPER_H_ */
