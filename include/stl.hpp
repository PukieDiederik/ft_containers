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

	// lexicographical_compare
	template <class InputIter1, class InputIter2>
	bool lexicographical_compare (InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
	{
		for(; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	template <class InputIter1, class InputIter2, class Compare>
	bool lexicographical_compare (InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compare comp)
	{
		for(; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// equal
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}
	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}
}

#endif
