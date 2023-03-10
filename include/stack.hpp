#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		Container c;
	public:
		// typedefs
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		// Constructors/Destructor
		explicit stack(const Container& cont = Container()) : c(cont) { }
		stack(const stack& copy) :c(copy.c) { }
		~stack () { }
		stack& operator=(const stack& copy) { c = copy.c; return *this; }

		// Accessors
		const_reference top() const { return c.back(); }
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }

		// Modification
		void push(const value_type& value) { c.push_back(value); }
		void pop() { c.pop_back(); }

		// Need to make these friends so they can access 'c'
		template <typename A,typename B>
		friend bool operator==(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);
		template <typename A,typename B>
		friend bool operator!=(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);
		template <typename A,typename B>
		friend bool operator<=(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);
		template <typename A,typename B>
		friend bool operator>=(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);
		template <typename A,typename B>
		friend bool operator<(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);
		template <typename A,typename B>
		friend bool operator>(const ft::stack<A, B> lhs, const ft::stack<A, B> rhs);

	};

	// Comparison operators
	template <typename T, typename Container>
	bool operator==(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c == rhs.c; }

	template <typename T, typename Container>
	bool operator!=(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c != rhs.c; }

	template <typename T, typename Container>
	bool operator<=(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c <= rhs.c; }

	template <typename T, typename Container>
	bool operator>=(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c >= rhs.c; }

	template <typename T, typename Container>
	bool operator<(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c < rhs.c; }

	template <typename T, typename Container>
	bool operator>(const ft::stack<T, Container> lhs, const ft::stack<T, Container> rhs)
	{ return lhs.c > rhs.c; }

}

#endif
