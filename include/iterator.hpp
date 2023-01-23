#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

//// iterator category tags
//namespace ft
//{
//	struct input_iterator_tag	{ };
//	struct output_iterator_tag	{ };
//	struct forward_iterator_tag			: public input_iterator_tag { };
//	struct bidirectional_iterator_tag	: public forward_iterator_tag { };
//	struct random_access_iterator_tag	: public bidirectional_iterator_tag { };
//}

// iterator_traits
namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

// Iterator base struct
namespace ft
{
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};
}

namespace ft
{
	template<typename Iterator>
	class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
												 typename ft::iterator_traits<Iterator>::value_type,
												 typename ft::iterator_traits<Iterator>::difference_type,
												 typename ft::iterator_traits<Iterator>::pointer,
												 typename ft::iterator_traits<Iterator>::reference >
	{
	protected:
		Iterator m_current;
	public:
		typedef Iterator												iterator_type;
		typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
		typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;

		// Constructors / Destructors
		reverse_iterator() :m_current(0) { }
		reverse_iterator(iterator_type x) :m_current(x) { }
		reverse_iterator(const reverse_iterator& x) :m_current(x.m_current) { }
		~reverse_iterator() { }

		iterator_type base() const { return m_current; }

		reference operator*() const { Iterator tmp = m_current; return *--tmp; }
		pointer operator->() const { Iterator tmp = m_current; --tmp; return tmp.operator->(); }

		reverse_iterator& operator++() { --m_current; return *this; }
		reverse_iterator operator++(int) { reverse_iterator tmp = *this; --m_current; return tmp; }
		reverse_iterator& operator--() { ++m_current; return *this; }
		reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++m_current; return tmp; }

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(m_current - n); }
		reverse_iterator& operator+=(difference_type n) { m_current -= n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(m_current + n); }
		reverse_iterator& operator-=(difference_type n) { m_current += n; return *this; }
	};

	// Comparison Operators
	template<typename Iter>
	bool operator==(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return x.base() == y.base(); }
	template<typename IterL, typename IterR>
	bool operator==(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return x.base() == y.base(); }

	template<typename Iter>
	bool operator!=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return !(x == y); }
	template<typename IterL, typename IterR>
	bool operator!=(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return !(x == y); }

	template<typename Iter>
	bool operator<(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return x.base() < y.base(); }
	template<typename IterL, typename IterR>
	bool operator<(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return x.base() < y.base(); }

	template<typename Iter>
	bool operator>(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return y < x; }
	template<typename IterL, typename IterR>
	bool operator>(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return y < x; }

	template<typename Iter>
	bool operator<=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return !(y < x); }
	template<typename IterL, typename IterR>
	bool operator<=(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return !(y < x); }

	template<typename Iter>
	bool operator>=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) { return !(x < y); }
	template<typename IterL, typename IterR>
	bool operator>=(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y) { return !(x < y); }

	//
	template<typename Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
									 const reverse_iterator<Iter>& it)
	{ return (reverse_iterator<Iter>(it - n)); }
	template<typename IterL, typename IterR>
	reverse_iterator<IterL> operator-(const reverse_iterator<IterL>& x, const reverse_iterator<IterR>& y)
	{ return (reverse_iterator<IterL>(x - y)); }
}

#endif
