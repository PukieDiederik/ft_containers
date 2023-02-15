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

		typedef BST<value_type, value_comp, value_equal_comp, Allocator> tree_type;
		//values
		tree_type m_tree;
	public:
		typedef value_comp value_compare;
		// Iterator typedefs
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef typename iterator_traits<iterator>::size_type		size_type;

		// Constructors & Destructors
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) { }
		template <typename InputIt>
		map (InputIt first, InputIt last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) { }
		map (const map& copy) { }
		~map() { }

		map& operator=(const map& copy) { m_tree = copy.m_tree; return *this; }

		T& at(const Key& key) { }
		const T& at (const Key& key) const { }
		T& operator[](const Key& key) { }

		iterator begin() { return m_tree.begin(); }
		const_iterator begin() const { return m_tree.begin(); }
		iterator end() { return m_tree.end(); }
		const_iterator end() const { return m_tree.end(); }

		reverse_iterator rbegin() { return m_tree.rbegin(); }
		const_reverse_iterator rbegin() const { return m_tree.rbegin(); }
		reverse_iterator rend() { return m_tree.rend(); }
		const_reverse_iterator rend() const { return m_tree.rend(); }

		bool empty() const { return m_tree.empty(); }
		size_type size() const { return m_tree.size(); }
		size_type max_size() const { return m_tree.max_size(); }

		void clear() { m_tree.clear(); }

		ft::pair<iterator, bool> insert ( const value_type& value) { }
		iterator insert (iterator pos, const value_type& value) { }
		template <typename InputIt>
		void insert(InputIt first, InputIt last) { }

		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		size_type erase(const Key& key);

		void swap( map& other) { m_tree.swap(other.m_tree); }

		size_type  count(const Key& key) const { }

		iterator find(const Key& key) { return m_tree.find(key); }
		const_iterator find(const Key& key) const { return m_tree.find(key); }

		ft::pair<iterator, iterator> equal_range(const Key& key) { }
		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { }

		iterator lower_bound(const Key& key) { return m_tree.lower_bound(key); }
		const_iterator lower_bound(const Key& key) const { return m_tree.lower_bound(key); }
		iterator upper_bound(const Key& key) { return m_tree.upper_bound(key); }
		const_iterator upper_bound(const Key& key) const { return m_tree.upper_bound(key); }

		key_compare key_comp() const;
		value_compare value_comp() const;
	};
}

#endif