#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "iterator.hpp"
#include "stl.hpp"
#include <cstddef> // Required for std::size_t
#include <memory> // required for std::allocator
#include <algorithm>
#include <stdexcept> // required for std::out_of_range

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	private:
		template<typename Pointer_T>
		class _iterator;
	public: // Type defintions

		typedef T			value_type;
		typedef Allocator	allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef _iterator<pointer>						iterator;
		typedef _iterator<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef std::size_t											size_type;


	private:

		// Iterator classes
		template<typename Base>
		class _iterator : public ft::iterator<std::random_access_iterator_tag, value_type>
		{
		protected:
			Base m_p;
			typedef typename ft::iterator_traits<Base> m_traits;


		public:
			// Type definitions
			typedef typename m_traits::iterator_category	iterator_category;
			typedef typename m_traits::value_type			value_type;
			typedef typename m_traits::difference_type		difference_type;
			typedef typename m_traits::reference			reference;
			typedef typename m_traits::pointer				pointer;

			// Constructors / Destructors
			_iterator() :m_p(NULL) { }
			_iterator(const _iterator& copy) :m_p(copy.m_p) { }
			_iterator(Base p) :m_p(p) { }
			~_iterator() { }

			_iterator& operator=(_iterator copy) { m_p = copy.m_p; return *this; }

			// Operators
			reference operator* () const { return *m_p; }
			pointer operator->() const { return m_p; }

			_iterator& operator++() { ++m_p; return *this; }
			_iterator operator++(int) { return _iterator(m_p++); }
			_iterator& operator--() { --m_p; return *this; }
			_iterator operator--(int) { return _iterator(m_p--); }
			reference operator[](difference_type n) const { return m_p[n]; }

			_iterator& operator+=(difference_type n) { m_p += n; return *this; }
			_iterator operator+(difference_type n) const { return _iterator(m_p + n); }
			_iterator operator+(_iterator n) const { return _iterator(m_p + n.m_p); }
			_iterator& operator-=(difference_type n) { m_p -= n; return *this; }
			_iterator operator-(difference_type n) const { return _iterator(m_p - n); }
			difference_type operator-(_iterator n) const { return m_p - n.m_p; }

			const Base& base() const { return m_p; }
		};
	private:
		pointer m_arr; // The internal array it will be using
		size_type m_size; // The amount of elements in this vector, this may differ from m_capacity
		size_type m_capacity; // The max internal size of the array
		allocator_type m_alloc; // The allocator

	public:
		// Constructors / Destructors
		explicit vector(const allocator_type& alloc = allocator_type()) : m_arr(NULL), m_size(0), m_capacity(0), m_alloc(alloc) { }
		explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			: m_size(count), m_capacity(count), m_alloc(alloc)
		{
			m_arr = m_alloc.allocate(count);
			std::fill_n(m_arr, count, value);
		}
		template<typename InputIt>
		vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
			   :m_size(0), m_capacity(0), m_alloc(alloc)
		{
			for(InputIt i = first; i != last; ++i)
				push_back(*i);
		}

		vector(const vector& copy) : m_size(copy.m_size), m_capacity(copy.m_capacity), m_alloc(copy.m_alloc) // Copy Constructor
		{
			m_arr = m_alloc.allocate(copy.m_capacity);
			std::copy(copy.cbegin(), copy.cend(), begin());
		}

		~vector()
		{
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
		}

		vector& operator=( const vector& copy) // Copy assignment
		{
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_alloc = copy.m_alloc;
			m_arr = m_alloc.allocate(copy.m_capacity);
			std::copy(copy.cbegin(), copy.cend(), m_arr);
			m_size = copy.m_size;
			m_capacity = copy.m_capacity;
			return *this;
		}

		void assign(size_type count, const_reference value) // Replaces the contents with 'count' copies of 'value'
		{
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_arr = NULL;
			m_size = 0;
			m_capacity = 0;
			resize(count, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last) // Replaces the contents with everything from 'first' to 'last'
		{
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_arr = NULL;
			m_capacity = 0;
			m_size = 0;
			for (InputIt i = first; i != last; ++i)
				push_back(*i);
		}
		allocator_type get_allocator() const { return m_alloc; }

		// Accessors
		reference at(size_type pos)
		{
			if (pos >= m_size)
				throw std::out_of_range("index out of range");
			return m_arr[pos];
		}
		const_reference at(size_type pos) const
		{
			if (pos >= m_arr)
				throw std::out_of_range("index out of range");
			return m_arr[pos];
		}

		reference operator[](size_type pos) { return m_arr[pos]; }
		const_reference operator[](size_type pos) const { return m_arr[pos]; }

		reference front() { return *m_arr; }
		const_reference front() const { return *m_arr; }

		reference back() { return m_arr[m_size - 1]; }
		const_reference back() const { return m_arr[m_size - 1]; }

		pointer data() { return m_arr; }
		const_pointer data() const { return m_arr; }

		iterator begin() { return iterator(m_arr); }
		const_iterator begin() const { return const_iterator(m_arr); }
		iterator end() { return iterator(m_arr + m_size); }
		const_iterator end() const { return const_iterator(m_arr + m_size); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		const_iterator cbegin() const { return const_iterator(m_arr); }
		const_iterator cend() const { return const_iterator(m_arr + m_size); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const {return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }
		size_type capacity() const { return m_capacity; }

		void reserve(size_type n)
		{
			if (n <= m_capacity)
				return;
			pointer tmp = m_alloc.allocate(n);
			std::copy(cbegin(), cend(), tmp);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_arr = tmp;
			m_capacity = n;
		}

		void shrink_to_fit()
		{
			if (m_size >= m_capacity)
				return;
			pointer tmp = m_alloc.allocate(m_size);
			std::copy(cbegin(), cend(), tmp);
			m_alloc.deallocate(m_arr, m_capacity);
			m_arr = tmp;
			m_capacity = m_size;
		}

		void resize(size_type count, value_type value = value_type())
		{
			if (count == m_size && m_size == m_capacity)
				return;
			pointer tmp = m_alloc.allocate(count);
			std::copy(cbegin(), (count > m_size) ? cend() : (cbegin() + count), tmp);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_arr = tmp;
			if (count > m_capacity)
				std::fill_n(m_arr + m_size, count - m_size, value);
			if (count < m_size)
				m_size = count;
			m_capacity = count;
		}

		//Modifiers
		void clear()
		{
			m_alloc.deallocate(m_arr, m_capacity);
			m_arr = NULL;
			m_size = 0;
			m_capacity = 0;
		}

		iterator insert(iterator pos, const value_type& value)
		{
			difference_type index = &*pos - m_arr;
			if (pos == end())
			{
				push_back(value);
				return end() - 1;
			}
			if (m_size == m_capacity)
				resize(m_capacity << 1);
			std::copy_backward(begin() + index, end(), end() + 1);
			m_size++;
			*(begin() + index) = value;
			return (begin() + index);
		}

		void insert(iterator pos, size_type n, const value_type& value)
		{
			difference_type index = &*pos - m_arr;
			if (m_size + n > m_capacity)
				resize(m_size + n);
			if (pos != end())
				std::copy_backward(begin() + index, end(), end() + n);
			m_size += n;
			std::fill_n(m_arr + index, n, value);
		}
		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
		{
			difference_type index = pos - begin();
			int n = std::distance(first, last);
			if (m_size + n > m_capacity)
				resize(m_size + n);
			if (begin() + index != end())
				std::copy_backward(begin() + index, end(), end() + n);
			std::copy(first, last, begin() + index);
			m_size += n;
		}

		iterator erase(iterator pos)
		{
			std::copy(pos + 1, end(), pos);
			m_size--;
			return pos;
		}
		iterator erase(iterator first, iterator last)
		{
			std::copy (last, end(), first);
			m_size -= last - first;
			return first;
		}

		void push_back(const value_type& value)
		{
			if (m_capacity == 0)
			{
				m_capacity = 1;
				m_arr = m_alloc.allocate(m_capacity);
				m_size = 1;
				*m_arr = value;
				return;
			}
			else if (m_size >= m_capacity)
			{
				resize(m_capacity << 1);
			}
			m_arr[m_size] = value;
			++m_size;
		}
		void pop_back()
		{
			if (m_size == 0)
				return;
			--m_size;
			if (m_size <= m_capacity >> 1)
				resize(m_capacity >> 1);
		}
		void swap(vector& other)
		{
			pointer tmp = m_arr;
			m_arr = other.m_arr;
			other.m_arr = tmp;

			size_type tmps = m_size;
			m_size = other.m_size;
			other.m_size = tmps;

			tmps = m_capacity;
			m_capacity = other.m_capacity;
			other.m_capacity = tmps;

			Allocator alloc = m_alloc;
			m_alloc = other.m_alloc;
			other.m_alloc = alloc;
		}

		// Iterator comparison operators
		template<typename IterL, typename IterR>
		friend bool operator==(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() == rhs.base(); }
		template<typename Iter>
		friend bool operator==(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() == rhs.base(); }

		template<typename IterL, typename IterR>
		friend bool operator!=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() != rhs.base(); }
		template<typename Iter>
		friend bool operator!=(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() != rhs.base(); }

		template<typename IterL, typename IterR>
		friend bool operator<(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() < rhs.base(); }
		template<typename Iter>
		friend bool operator<(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() < rhs.base(); }

		template<typename IterL, typename IterR>
		friend bool operator>(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() > rhs.base(); }
		template<typename Iter>
		friend bool operator>(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() > rhs.base(); }

		template<typename IterL, typename IterR>
		friend bool operator<=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() <= rhs.base(); }
		template<typename Iter>
		friend bool operator<=(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() <= rhs.base(); }

		template<typename IterL, typename IterR>
		friend bool operator>=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{ return lhs.base() >= rhs.base(); }
		template<typename Iter>
		friend bool operator>=(const _iterator<Iter>& lhs, const _iterator<Iter>& rhs)
		{ return lhs.base() >= rhs.base(); }
	};

	// Operators
	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(rhs < lhs); }
	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return rhs < lhs; }
	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y);
}

#endif