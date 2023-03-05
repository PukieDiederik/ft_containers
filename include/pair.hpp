#ifndef PAIR_HPP
#define PAIR_HPP

#include "stl.hpp"

namespace ft
{
	template<typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		// Constructors
		pair() : first(), second() { }
		pair(const T1& x, const T2& y) :first(x), second(y) { }
		template<typename U1, typename U2>
		pair(const pair<U1, U2>& p) :first(p.first), second(p.second) { }

		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }

	// Comparison operators
	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs == rhs); }

	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return ((lhs.first != rhs.first) ? (lhs.first < rhs.first) : (lhs.second < rhs.second)); }

	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(rhs < lhs); }

	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (rhs < lhs); }

	template <typename T1, typename T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs < rhs); }
}

#endif
