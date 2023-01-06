#ifndef STL_HPP
#define STL_HPP

namespace ft
{
	// integral constant, required for compile time checking of types
	template <typename T, T Val>
	struct integral_constant
	{
		static const T value = Val;
		typedef T value_type;
		typedef integral_constant<T, Val> type;
	};

	template <typename T, T Val>
	const T integral_constant<T, Val>::value;

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// Removes const so I don't have to do way more checking in is_integral
	template<typename T> struct remove_const { typedef T type; };
	template<typename T> struct remove_const<const T> { typedef T type; };

	// is_integral
	template <typename T>
	struct is_integral : public false_type { };
	template <typename T>
struct is_integral<const T> : public is_integral<typename remove_const<T>::type> { };

	template <> struct is_integral<bool> : public true_type { };
	template <> struct is_integral<char> : public true_type { };
	template <> struct is_integral<signed char> : public true_type { };
	template <> struct is_integral<unsigned char> : public true_type { };
	template <> struct is_integral<wchar_t> : public true_type { };
	template <> struct is_integral<short> : public true_type { };
	template <> struct is_integral<unsigned short> : public true_type { };
	template <> struct is_integral<int> : public true_type { };
	template <> struct is_integral<unsigned int> : public true_type { };
	template <> struct is_integral<long> : public true_type { };
	template <> struct is_integral<unsigned long> : public true_type { };

	// enable_if
	template<bool B, class T = void>
	struct enable_if { };
	template <class T>
	struct enable_if<true, T> { typedef T type; };
}

#endif
