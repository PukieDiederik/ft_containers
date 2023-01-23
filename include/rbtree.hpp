#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "pair.hpp"
#include <functional>
#include <memory>

namespace ft
{
	template <typename T, typename Compare = std::less<T>, typename EqualsCompare = std::equal_to<T>, typename Allocator = std::allocator<T>>
	class RedBlackTree
	{
	public:
		typedef T				value_type;
		typedef Compare			compare_type;
		typedef EqualsCompare	equals_to_type;
		typedef Allocator		allocator_type;
		// TODO: difference types
		typedef std::size_t		size_type;
		// TODO: iterators
	private:
		size_type m_size;
		Allocator m_alloc;

	public:
		// Constructors/Destructors
		RedBlackTree();
		explicit RedBlackTree(const Compare& comp, const Allocator& alloc = Allocator());
		// TODO: iterator constructor
		RedBlackTree(const RedBlackTree& copy);

		~RedBlackTree();

		// TODO: iterators

		// Capacity
		bool empty() const { return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }

		// modifiers
		void clear();

//		ft::pair<iterator, bool> insert(const value_type& value);
//		iterator insert(iterator pos, const value_type& value);
		template<typename InputIt>
		void insert(InputIt first, InputIt last);

//		void erase(iterator pos);
//		void erase(iterator first, iterator last);

		void swap(RedBlackTree& other);

		// lookup
//		iterator find(const value_type& v);
//		const_iterator find (const value_type& v);

		iterator lower_bound(const value_type& v);
		iterator higher_bound(const value_type& v);
	};

	template <typename T, typename Compare = std::less<T>, typename EqualsCompare = std::equal_to<T>, typename Allocator = std::allocator<T>>
	void swap(typename ft::RedBlackTree<T, Compare, EqualsCompare, Allocator>& lhs,
			  typename ft::RedBlackTree<T, Compare, EqualsCompare, Allocator>& rhs)
	{ lhs.swap(rhs); }
}

#endif
