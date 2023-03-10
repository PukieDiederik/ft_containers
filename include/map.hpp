#ifndef MAP_HPP
#define MAP_HPP

#include "bst.hpp"
#include <stdexcept>

namespace ft
{
	template<typename Key,
			 typename T,
			 typename Compare = std::less<Key>,
	         typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
		typedef BST<const Key, T, Compare, Allocator> tree_type;
		tree_type m_tree;

	public:
		// Typedefs
		typedef Key 				key_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;

		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef typename std::size_t 								size_type;

		class value_compare
		{
			friend class map<Key, T, Compare, Allocator>;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) { }
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		// Constructors / Destructors
		explicit map(const key_compare& comp = key_compare(Compare()),
					 const allocator_type& alloc = allocator_type())
			:m_tree(tree_type(comp)) { (void)alloc; }

		template <typename InputIt>
		map (InputIt first, InputIt last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type())
			:m_tree(tree_type(comp))
		{
			while (first != last)
			{
				m_tree.insert(*first);
				++first;
			}
			(void) alloc;
		}
		map (const map& copy) :m_tree(copy.m_tree) { }
		~map() { }

		map& operator=(const map& copy) { m_tree = copy.m_tree; return *this; }

		// Accessors
		T& at(const Key& key)
		{
			iterator i = m_tree.find(key);
			// Throws exception if the key is not found
			if (i == m_tree.end())
				throw std::out_of_range("key not found");
			return (*i).second;
		}
		const T& at (const Key& key) const
		{
			const_iterator i = m_tree.find(key);
			// Throws exception if the key is not found
			if (i == m_tree.end())
				throw std::out_of_range("key not found");
			return i->second;
		}

		T& operator[](const Key& key)
		{
			iterator i = m_tree.find(key);
			if (i != m_tree.end())
				return i->second;
			return m_tree.insert(value_type(key,T())).first->second;
		}

		size_type  count(const Key& key) const
		{ return (m_tree.find(key) == m_tree.end()) ? 0 : 1; }

		iterator find(const Key& key) { return m_tree.find(key); }
		const_iterator find(const Key& key) const { return m_tree.find(key); }

		// Iterators
		iterator begin() { return m_tree.begin(); }
		const_iterator begin() const { return m_tree.begin(); }
		iterator end() { return m_tree.end(); }
		const_iterator end() const { return m_tree.end(); }

		reverse_iterator rbegin() { return m_tree.rbegin(); }
		const_reverse_iterator rbegin() const { return m_tree.rbegin(); }
		reverse_iterator rend() { return m_tree.rend(); }
		const_reverse_iterator rend() const { return m_tree.rend(); }

		// Size
		bool empty() const { return m_tree.empty(); }
		size_type size() const { return m_tree.size(); }
		size_type max_size() const { return m_tree.max_size(); }

		// Modification
		void clear() { m_tree.clear(); }

		ft::pair<iterator, bool> insert ( const value_type& value) { return m_tree.insert(value); }
		iterator insert(iterator position, const value_type& value)
		{ (void)position; return m_tree.insert(value).first; }
		template <typename InputIt>
		void insert(InputIt first, InputIt last)
		{
			for(; first != last; ++first)
				m_tree.insert(*first);
		}

		iterator erase(iterator pos) { return m_tree.erase(pos); }
		iterator erase(iterator first, iterator last)
		{
			while ( first != last)
				m_tree.erase(first++);
			return last;
		}
		size_type erase(const Key& key)
		{
			iterator i = m_tree.find(key);
			if (i == m_tree.end())
				return 0;
			m_tree.erase(i);
			return 1;
		}


		// Range / Bounds
		ft::pair<iterator, iterator> equal_range(const Key& key)
		{ return ft::pair<iterator,iterator>(lower_bound(key), upper_bound(key)); }
		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{ return ft::pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));}

		iterator lower_bound(const Key& key) { return m_tree.lower_bound(key); }
		const_iterator lower_bound(const Key& key) const { return m_tree.lower_bound(key); }
		iterator upper_bound(const Key& key) { return m_tree.upper_bound(key); }
		const_iterator upper_bound(const Key& key) const { return m_tree.upper_bound(key); }

		// Other
		void swap( map& other) {m_tree.swap(other.m_tree);}

		key_compare key_comp() const { return key_compare(); }
		value_compare value_comp() const { return value_compare(key_compare()); }
		allocator_type get_allocator() const { return m_tree.get_allocator();}
	};

	// Comparison operators
	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{ return !(lhs == rhs); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator<=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{return !(rhs < lhs); }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{return rhs < lhs; }

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
	{return !(lhs < rhs); }
}

// Although overloading anything in STD namespace is technically illegal. This vector needs to function
// like a std::vector. The only way I found to do this is to overload std::swap.
// For more info: https://stackoverflow.com/a/7108123
namespace std
{
	template<typename Key, typename T, typename Compare, typename Allocator>
	void swap(ft::map<Key, T, Compare, Allocator>& lhs, ft::map<Key, T, Compare, Allocator>& rhs) { lhs.swap(rhs); }
}

#endif
