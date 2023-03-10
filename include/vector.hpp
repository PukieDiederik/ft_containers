#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "iterator.hpp"
#include "stl.hpp"
#include <algorithm>
#include <cstddef> // Required for std::size_t
#include <cstring>
#include <memory> // required for std::allocator
#include <stdexcept> // required for std::out_of_range

namespace ft
{
	// Iterator class for vector (and other pointers in general)
	template<typename Base>
	class _iterator : public ft::iterator<std::random_access_iterator_tag, Base>
	{
	public:
		// Type definitions
		typedef std::random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;
		typedef Base							value_type;
		typedef Base&							reference;
		typedef Base*							pointer;
		typedef const Base&						const_reference;
		typedef const Base*						const_pointer;

	protected:
		pointer m_p;

	public:
		// Constructors / Destructors
		_iterator() :m_p(NULL) { }
		_iterator(const _iterator& copy) :m_p(copy.m_p) { }
		_iterator(pointer p) :m_p(p) { }
		~_iterator() { }

		_iterator& operator=(_iterator copy) { m_p = copy.m_p; return *this; }
		//conversion from normal to const
		operator _iterator<const Base> () const { return _iterator<const Base>(m_p); }

		// Operators
		reference operator* () const { return *m_p; }
		pointer operator->() const { return m_p; }

		// Increment / Decrement
		_iterator& operator++() { ++m_p; return *this; }
		_iterator operator++(int) { return _iterator(m_p++); }
		_iterator& operator--() { --m_p; return *this; }
		_iterator operator--(int) { return _iterator(m_p--); }

		_iterator& operator+=(difference_type n) { m_p += n; return *this; }
		_iterator operator+(difference_type n) const { return _iterator(m_p + n); }
		_iterator operator+(_iterator n) const { return _iterator(m_p + n.m_p); }
		_iterator& operator-=(difference_type n) { m_p -= n; return *this; }
		_iterator operator-(difference_type n) const { return _iterator(m_p - n); }

		// Access
		reference operator[](difference_type n) const { return m_p[n]; }

		difference_type operator-(_iterator n) const { return m_p - n.m_p; }

		const const_pointer & base() const { return m_p; }
	};

	// Operator + and - when you use `n + iterator` instead of `iterator + n`
	template<typename Base>
	_iterator<Base> operator+(typename _iterator<Base>::difference_type n,
										 _iterator<Base> i)
	{ return i + n; }
	template<typename Base>
	_iterator<Base> operator-(typename _iterator<Base>::difference_type n,
							  _iterator<Base> i)
	{ return i - n; }

	// Iterator comparison operators
	template<typename IterL, typename IterR>
	bool operator==(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() == rhs.base(); }

	template<typename IterL, typename IterR>
	bool operator!=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() != rhs.base(); }

	template<typename IterL, typename IterR>
	bool operator<(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() < rhs.base(); }

	template<typename IterL, typename IterR>
	bool operator>(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() > rhs.base(); }

	template<typename IterL, typename IterR>
	bool operator<=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template<typename IterL, typename IterR>
	bool operator>=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
	{ return lhs.base() >= rhs.base(); }


	// Vector class
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		// Type definitions
		typedef T											value_type;
		typedef Allocator									allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef _iterator<value_type>				iterator;
		typedef _iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		typedef typename iterator::difference_type			difference_type;
		typedef std::size_t									size_type;

	private:
		// Variables
		pointer m_arr; // The internal array it will be using
		size_type m_size; // The amount of elements in this vector, this may differ from m_capacity
		size_type m_capacity; // The max internal size of the array
		allocator_type m_alloc; // The allocator

	public:
		// Constructors / Destructors
		explicit vector(const allocator_type& alloc = allocator_type())
			: m_arr(NULL), m_size(0), m_capacity(0), m_alloc(alloc) { }

		explicit vector(size_type count, const value_type& value = value_type(),
			const allocator_type& alloc = allocator_type())
			: m_arr(NULL), m_size(count), m_capacity(count), m_alloc(alloc)
		{
			if (count)
				m_arr = m_alloc.allocate(count);
			if (!m_arr)
				return;
			for (size_type i = 0; i < count; ++i)
				m_alloc.construct(m_arr + i, value);
		}

		template<typename InputIt>
		vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
			   :m_arr(0), m_size(0), m_capacity(0), m_alloc(alloc)
		{
			reserve(std::distance(first, last));
			for(size_type i = 0; first != last; ++first, ++i)
				m_alloc.construct(m_arr + i, *first);
			m_size = m_capacity;
		}

		vector(const vector& copy) : m_arr(NULL), m_size(copy.m_size), m_capacity(copy.m_capacity), m_alloc(copy.m_alloc) // Copy Constructor
		{
			if (m_capacity != 0)
				m_arr = m_alloc.allocate(m_capacity);
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.construct(m_arr + i, copy.m_arr[i]);
		}


		~vector()
		{
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.destroy(m_arr + i);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
		}

		vector& operator=( const vector& copy) // Copy assignment
		{
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.destroy(m_arr + i);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			m_capacity = copy.m_capacity;
			m_alloc = copy.m_alloc;
			m_arr = m_alloc.allocate(m_capacity);
			m_size = copy.m_size;
			for(size_type i = 0; i < m_size; ++i)
				m_alloc.construct(m_arr + i, copy.m_arr[i]);
			return *this;
		}


		// Functions
		void assign(size_type count, const_reference value)
		{
			// Destroy existing elements
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.destroy(m_arr + i);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			// Reset variables
			m_arr = NULL;
			m_size = 0;
			m_capacity = 0;
			// Resize and add new elements
			resize(count, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
		{
			// Destroy existing elements
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.destroy(m_arr + i);
			if (m_arr)
				m_alloc.deallocate(m_arr, m_capacity);
			// Reset variables
			m_arr = NULL;
			m_capacity = 0;
			m_size = 0;
			// Add new elements
			for (InputIt i = first; i != last; ++i)
				push_back(*i);
		}

		// Accessors
		reference at(size_type pos)
		{
			if (pos >= m_size)
				throw std::out_of_range("index out of range");
			return m_arr[pos];
		}
		const_reference at(size_type pos) const
		{
			if (pos >= m_size)
				throw std::out_of_range("index out of range");
			return m_arr[pos];
		}

		reference operator[](size_type pos)				{ return m_arr[pos]; }
		const_reference operator[](size_type pos) const	{ return m_arr[pos]; }

		reference front()				{ return *m_arr; }
		const_reference front() const	{ return *m_arr; }
		reference back()				{ return m_arr[m_size - 1]; }
		const_reference back() const	{ return m_arr[m_size - 1]; }

		// Iterators
		iterator begin()				{ return iterator(m_arr); }
		const_iterator begin() const	{ return const_iterator(m_arr); }
		iterator end()					{ return iterator(m_arr + m_size); }
		const_iterator end() const		{ return const_iterator(m_arr + m_size); }

		reverse_iterator rbegin()				{ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const	{ return const_reverse_iterator(end()); }
		reverse_iterator rend() 				{ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const		{ return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const {return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }
		size_type capacity() const { return m_capacity; }

		// Reserves at least 'n' amount of space
		void reserve(size_type n)
		{
			// If we already have enough capacity, do nothing
			if (n <= m_capacity)
				return;

			// Allocate new array
			pointer tmp = m_alloc.allocate(n);
			// Copy array over and destroy old array
			if (m_arr)
			{
				for (size_type i = 0; i < m_size; ++i)
				{
					m_alloc.construct(tmp + i, m_arr[i]);
					m_alloc.destroy(m_arr + i);
				}
				m_alloc.deallocate(m_arr, m_capacity);
			}
			// Update variables
			m_arr = tmp;
			m_capacity = n;
		}

		void shrink_to_fit()
		{
			if (m_size >= m_capacity)
				return;
			// Allocate new array
			pointer tmp = m_alloc.allocate(m_size);
			// Copy elements over and destroy old ones
			for(size_type i = 0; i < m_size; ++i) {
				m_alloc.construct(tmp + i, m_arr[i]);
				m_alloc.destroy(m_arr + i);
			}
			m_alloc.deallocate(m_arr, m_capacity);
			// Update variables
			m_arr = tmp;
			m_capacity = m_size;
		}

		void resize(size_type count, value_type value = value_type())
		{
			// If the 'count' is less than our current size, we need to delete elements
			if (count <= m_size) {
				for (size_type i = count; i < m_size; ++i)
					m_alloc.destroy(m_arr + i);
				m_size = count;
				return;
			}

			// Make sure we have enough capacity
			reserve(count);
			// Construct new elements
			for(size_type i = 0; i < count - m_size; ++i)
				m_alloc.construct(m_arr + m_size + i, value);
			m_size = count;
		}

		//Modifiers
		void clear()
		{
			for (size_type i = 0; i < m_size; ++i)
				m_alloc.destroy(m_arr + i);
			m_size = 0;
		}

		iterator insert(iterator pos, const value_type& value)
		{
			// Get index of where to insert, this is important because we might need to reallocate (invalidating pos)
			difference_type index = &*pos - m_arr;

			// If we need to insert at the end, just use push_back
			if (pos == end())
			{
				push_back(value);
				return end() - 1;
			}

			// Make sure we have enough capacity
			if (m_size == m_capacity)
				reserve(m_capacity << 1);
			// Construct a new element at the end
			m_alloc.construct(m_arr + m_size, value_type());
			// Move old values back by 1
			std::copy_backward(begin() + index, end(), end() + 1);
			// Insert new value
			*(m_arr + index) = value;
			m_size++;
			return (begin() + index);
		}

		void insert(iterator pos, size_type n, const value_type& value)
		{
			// Get index of where to insert, this is important because we might need to reallocate (invalidating pos)
			difference_type index = &*pos - m_arr;

			// Reserve enough space
			reserve(m_size + n);
			// Construct new elements at end
			for(size_type i = 0; i < n; ++i)
				m_alloc.construct(m_arr + m_size + i, value_type());
			// Move elements to back
			if (m_arr + index != m_arr + m_size)
				std::copy_backward(begin() + index, end(), end() + n);
			// Insert new elements
			std::fill_n(m_arr + index, n, value);
			m_size += n;
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
		{
			pointer tmp = m_arr; // tmp might be reallocated if necessary
			difference_type index = pos - begin(); // Index of where to insert
			size_type n = std::distance(first, last); // Amount of elements to insert

			// Allocate new space if necessary (can't use reserve because iterators might be in current vector)
			if (m_size + n > m_capacity)
			{
				tmp = m_alloc.allocate(m_size + n);
				for (size_type i = 0; i < m_size; ++i)
					m_alloc.construct(tmp + i, m_arr[i]);
			}

			// Construct new elements at the end
			for(size_type i = 0; i < n; ++i)
				m_alloc.construct(tmp + m_size + i, value_type());
			// Move elements to back
			if (begin() + index != end())
				std::copy_backward(tmp + index, tmp + m_size, tmp + m_size + n);
			// Insert new elements
			for (InputIt i = first; i != last; ++i, ++index)
				tmp[index] = *i;

			// Destroy old elements if it needed to be reallocated
			if(m_arr != tmp)
			{
				for (size_t i = 0; i < m_size; ++i)
					m_alloc.destroy(m_arr + i);
				m_alloc.deallocate(m_arr, m_capacity);
				m_capacity = m_size + n;
			}
			m_size += n;
			m_arr = tmp;
		}

		iterator erase(iterator pos)
		{
			// Destroy element at pos
			m_alloc.destroy(&*pos);
			// Construct a new element at pos
			m_alloc.construct(&*pos, value_type());
			// Copy the back 1 forward
			std::copy(pos + 1, end(), pos);
			m_size--;
			// Destroy end element (should not be used anymore)
			m_alloc.destroy(&*end());
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			// Destroy and construct new elements in positions
			for(iterator i = first; i != last; ++i) {
				m_alloc.destroy(&(*i));
				m_alloc.construct(&*i, value_type());
			}
			// Copy back forward
			std::copy(last, end(), first);
			size_type n = std::distance(first, last);
			// Destroy N elements at the end
			for (size_type i = 0; i < n; ++i)
				m_alloc.destroy((&*end()) - i - 1);
			m_size -= n;
			return first;
		}

		void push_back(const value_type& value)
		{
			// If empty reserve space for at least 1 element
			if (m_capacity == 0)
				reserve(1);
			// If more space is required, double capacity
			else if (m_size >= m_capacity)
				reserve(m_capacity << 1);
			// Construct new element at end
			m_alloc.construct(m_arr + m_size, value);
			++m_size;
		}
		void pop_back()
		{
			if (m_size == 0)
				return;
			m_alloc.destroy(m_arr + m_size - 1);
			--m_size;
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

		pointer data() { return m_arr; }
		const_pointer data() const { return m_arr; }
		allocator_type get_allocator() const { return m_alloc; }
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
}

// Although overloading anything in STD namespace is technically illegal. This vector needs to function
// like a std::vector. The only way I found to do this is to overload std::swap.
// For more info: https://stackoverflow.com/a/7108123
namespace std
{
	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif
