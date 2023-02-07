#ifndef MAP_HPP
#define MAP_HPP

#include "bst.hpp"

namespace ft
{
	template<typename Key,
			 typename T,
			 typename Compare = std::less<Key>,
	         typename Allocator = std::allocator<ft::pair<Key, T> > >
	class map
	{
	public: // Typedefs
		typedef Key key_type;
		typedef ft::pair<Key, T> value_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;

		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		// TODO: iterators
	private: // comparing classes
		class value_comp
		{
		protected:
			Compare comp;
			value_comp (Compare c) : comp(c) { }
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		class value_equal_comp
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const
			{
				return x.first == y.first;
			}
		};

	public:
		typedef value_comp value_compare;

	};
}

#endif