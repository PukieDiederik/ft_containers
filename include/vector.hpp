#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <cstddef> // Required for std::size_t
#include "iterator.hpp"
#include <memory>

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public: // Type defintions
		typedef T			value_type;
		typedef Allocator	allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		// TODO: Iterators

		//TODO: update this to use iterator_traits<iterator>::difference_type instead
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t		size_type;


	private:
		pointer m_arr; // The internal array it will be using
		size_type m_size; // The amount of elements in this vector, this may differ from m_max_size
		size_type m_max_size; // The max internal size of the array
		Allocator m_alloc; // The allocator

	public:
		// Constructors / Destructors
		vector() { }
		explicit vector(const Allocator& alloc) { }
		explicit vector(size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator()) { }
		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) { }
//		vector(const vector& copy) { } // Copy Constructor

		~vector() { }

//		vector& operator=( const vector& other ); // Copy assignment
//		void assign(size_type count, const_reference value); // Replaces the contents with 'count' copies of 'value'
//		template<class InputIt>
//		void assign(InputIt first, InputIt last); // Replaces the contents with everything from 'first' to 'last'
//		Allocator get_allocator() const;

		// Accessors
//		reference at(size_type pos);
//		const_reference at(size_type pos) const;
//
//		reference operator[](size_type pos);
//		const_reference operator[](size_type pos) const;
//
//		reference front();
//		const_reference front() const;
//
//		reference back();
//		const_reference back() const;
//
//		pointer data();
//		const_pointer data() const;

		// TODO: Iterators

		// Capacity
//		bool empty() const;
//		size_type size() const;
//		size_type max_size() const;
//		size_type capacity() const;

//		void reserve(size_type new_cap);
//		void shrink_to_fit();
//		void resize(size_type count, value_type value = value_type());

		//Modifiers
//		void clear();
//		iterator insert(iterator pos, const T& value);
//		void insert(iterator pos, size_type n, const value_type& val);
//		template<class InputIt>
//		void insert(iterator pos, InputIt first, InputIt last);
//		iterator erase(iterator pos);
//		iterator erase(iterator first, iterator last);
//		void push_back(const value_type& value);
//		void pop_back();
		void swap(vector& other) { }
	};

	// Operators
	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y);
}

#endif