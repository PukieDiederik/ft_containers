#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include "stl.hpp"
#include <functional>
#include <memory>
#include <iostream>
#include <queue>

#include <iostream>

namespace ft
{
	// Nodes for binary tree
	template<typename T>
	struct _TreeNode
	{
		T value;

		_TreeNode* parent;
		_TreeNode* left;
		_TreeNode* right;

		_TreeNode() : value(), parent(NULL), left(NULL), right(NULL) { }
		_TreeNode(const T& v, _TreeNode* _parent, _TreeNode* _nil) :value(v), parent(_parent), left(_nil), right(_nil) { }
		_TreeNode(const _TreeNode& copy) :value(copy.value), parent(copy.parent), left(copy.left), right(copy.right) { }

		_TreeNode<T>& operator=(const _TreeNode<T>& copy)
		{
			value = copy.value;
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
			return *this;
		}

		_TreeNode *left_most()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->left->isDummy())
				tmp = tmp->left;
			return tmp;
		}

		_TreeNode *right_most()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->right->isDummy())
				tmp = tmp->right;
			return tmp;
		}

		_TreeNode* left_most() const
		{
			const _TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->left->isDummy())
				tmp = tmp->left;
			return tmp;
		}

		_TreeNode* right_most() const
		{
			const _TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->right->isDummy())
				tmp = tmp->right;
			return tmp;
		}

		_TreeNode* left_most_leaf()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->left->isDummy()) ? tmp->right : tmp->left;
			return tmp;
		}
		_TreeNode* right_most_leaf()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->right->isDummy()) ? tmp->left : tmp->right;
			return tmp;
		}

		const _TreeNode* left_most_leaf() const
		{
			const _TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->left->isDummy()) ? tmp->right : tmp->left;
			return tmp;
		}
		const _TreeNode* right_most_leaf() const
		{
			const _TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->right->isDummy()) ? tmp->left : tmp->right;
			return tmp;
		}

		inline bool isDummy() const { return (!left && !right); }
		inline bool isLeaf() const { return left->isDummy() && right->isDummy(); }
	};

	// Iterator for map/BST
	template<typename T, typename N>
	class _bst_iterator : public ft::iterator<std::bidirectional_iterator_tag, N*>
	{
	private:
		typedef ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, N*> > m_traits;
		typedef N* Base;
	protected:
		Base m_base;

	public:
		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;
		typedef const T&	const_reference;
		typedef const T*	const_pointer;


		//constructors
		_bst_iterator() : m_base(NULL) { }
		_bst_iterator(Base base) : m_base(base) { }
		_bst_iterator(const _bst_iterator& copy) : m_base(copy.m_base) { }

		~_bst_iterator() { }

		_bst_iterator& operator=(const _bst_iterator& copy) { m_base = copy.m_base; return *this;}

		operator _bst_iterator<const value_type, const N> () const
		{
			return _bst_iterator<const value_type, const N>(m_base);
		}

		_bst_iterator& operator++()
		{
			if (m_base->isDummy())
			{
				m_base = m_base->parent;
				return *this;
			}
			if (!m_base->parent && m_base->right->isDummy())
			{
				m_base = m_base->right;
				return *this;
			}
			if (m_base->right->isDummy())
			{
				// if this node is the left side
				if (m_base->parent->left == m_base)
				{
					m_base = m_base->parent;
					return *this;
				}
				else // if the node is the right side
				{
					Base tmp = m_base;
					while (tmp != tmp->parent->left)
					{
						tmp = tmp->parent;
						if (!tmp->parent)
						{
							m_base = m_base->right;
							return *this;
						}
					}
					m_base = tmp->parent;
					return *this;
				}
			}
			else
			{
				Base tmp = m_base->right;
				while (!tmp->left->isDummy())
				{
					tmp = tmp->left;
				}
				m_base = tmp;
				return *this;
			}
		}

		_bst_iterator operator++(int)
		{
			_bst_iterator tmp(*this);
			operator++();
			return tmp;
		}

		_bst_iterator& operator--()
		{
			if (m_base->isDummy())
			{
				m_base = m_base->parent;
				return *this;
			}
			if (!m_base->parent && m_base->left->isDummy())
			{
				m_base = m_base->left;
				return *this;
			}
			if (m_base->left->isDummy())
			{
				// if this node is the right side
				if (m_base->parent->right == m_base)
				{
					m_base = m_base->parent;
					return *this;
				}
				else // if the node is the left side
				{
					Base tmp = m_base;
					while (tmp != tmp->parent->right)
					{
						tmp = tmp->parent;
						if (!tmp->parent)
						{
							m_base = m_base->left;
							return *this;
						}
					}
					m_base = tmp->parent;
					return *this;
				}
			}
			else
			{
				Base tmp = m_base->left;
				while (!tmp->right->isDummy())
				{
					tmp = tmp->right;
				}
				m_base = tmp;
				return *this;
			}
		}
		_bst_iterator operator--(int)
		{
			_bst_iterator tmp(*this);
			operator--();
			return tmp;
		}

		reference operator* ()
		{
			return m_base->value;
		}

		pointer operator-> ()
		{
			return &m_base->value;
		}

		const_reference operator* () const
		{
			return m_base->value;
		}


		const_pointer operator-> () const
		{
			return &m_base->value;
		}

		bool operator==(const _bst_iterator& rhs) const
		{
			return m_base == rhs.base();
		}

		bool operator!=(const _bst_iterator& rhs) const
		{
			return m_base != rhs.base();
		}

		const Base& base() const { return m_base; }
	};

	// BST
	template <typename Key, typename T,
			  typename Compare = std::less<const Key>,
			  typename Allocator = std::allocator<ft::pair<Key, T> > >
	class BST
	{
	private:
		// We will need a treenode allocator instead of value_type
		typedef typename Allocator::template rebind<_TreeNode<ft::pair<const Key, T> > >::other _alloc;

	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef _alloc					allocator_type;
		typedef Compare					value_compare;

		typedef _TreeNode<value_type>	node_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef value_type*				pointer;
		typedef const value_type*		const_pointer;

		typedef _bst_iterator<value_type, node_type>				iterator;
		typedef _bst_iterator<const value_type, const node_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

	private:
		// Variables
		size_type 		m_size;
		_alloc			m_alloc;
		const Compare	m_comp;

		node_type*	m_nil_node;
		node_type*	m_root;

	public:
		// Constructors/Destructors
		explicit BST(Compare comp = Compare())
			:m_size(0), m_alloc(), m_comp(comp), m_nil_node(m_alloc.allocate(1)), m_root(m_nil_node)
		{
			m_alloc.construct(m_nil_node, node_type(value_type(), NULL, NULL));
		}

		BST(const BST& copy)
			:m_size(0), m_alloc(copy.m_alloc), m_comp(copy.m_comp), m_nil_node(m_alloc.allocate(1)),m_root(m_nil_node)
		{
			// Construct new nil node
			m_alloc.construct(m_nil_node, node_type(value_type(), NULL, NULL));
			*this = copy;
		}

		~BST()
		{
			clear();
			m_alloc.destroy(m_nil_node);
			m_alloc.deallocate(m_nil_node, 1);
		}

		BST& operator=(const BST& copy)
		{
			// Make the sure the current BST is empty
			clear();
			// if there is nothing to copy, just skip
			if (copy.empty())
				return *this;
			// Insert new nodes DFS
			std::queue<node_type*> q;
			q.push(copy.m_root);
			while (!q.empty())
			{
				insert(q.front()->value);
				if (!q.front()->left->isDummy())
					q.push(q.front()->left);
				if (!q.front()->right->isDummy())
					q.push(q.front()->right);
				q.pop();
			}
			return *this;
		}

		// Iterators
		iterator begin()				{ return iterator(m_root->left_most()); }
		const_iterator begin() const	{ return const_iterator(m_root->left_most()); }
		iterator end()					{ return iterator(m_nil_node); }
		const_iterator end() const		{ return const_iterator(m_nil_node); }

		reverse_iterator rbegin()				{ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const	{ return const_reverse_iterator (end()); }
		reverse_iterator rend()					{ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const		{ return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const { return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }

		// modifiers
		void clear()
		{
			if (m_root->isDummy())
				return;

			// Find the left most leaf node, then keep going until we're finished
			for (node_type* i = m_root->left_most_leaf(), *next; i != NULL; i = next)
			{
				// Figure out which node is next
				if (i->parent && i->parent->right != i && !i->parent->right->isDummy())
					next = i->parent->right->left_most_leaf();
				else
					next = i->parent;

				// Destroy current node
				m_alloc.destroy(i);
				m_alloc.deallocate(i, 1);
			}
			// Set root to be the nil node
			m_root = m_nil_node;
			// Fix nil node's parent
			m_nil_node->parent = NULL;
			m_size = 0;
		}

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			node_type* cur = m_root;
			node_type** pref; // a pointer to which side of cur it should be inserted

			// If the map is empty
			if (cur->isDummy())
			{
				m_root = m_alloc.allocate(1);
				m_alloc.construct(m_root, node_type(value, NULL, m_nil_node));
				m_nil_node->parent = m_root;
				++m_size;
				return ft::make_pair<iterator, bool>(iterator(m_root), true);
			}

			// find place to insert
			while (!cur->isDummy() && cur->value.first != value.first)
			{
				if (m_comp(value.first, cur->value.first))
					pref = &cur->left;
				else
					pref = &cur->right;

				// Checks if we have found the place to insert
				if ((*pref)->isDummy())
					break;
				else
					cur = *pref;
			}
			// If we found the key, do not insert it
			if (cur->value.first == value.first)
				return ft::make_pair<iterator, bool>(iterator(cur), false);

			// Create new node
			*pref = m_alloc.allocate(1);
			m_alloc.construct(*pref, node_type(value, cur, m_nil_node));
			++m_size;
			// Fix nil node
			if (m_nil_node->parent == cur && pref == &cur->right)
				m_nil_node->parent = *pref;
			return ft::make_pair<iterator, bool>(iterator(*pref), true);
		}

	private:
		void erase_helper(node_type* n, node_type* lhs)
		{
			if (n->parent)
			{
				if (n == n->parent->left)
					n->parent->left = lhs;
				else
					n->parent->right = lhs;
			}
			else
				m_root = lhs;

			if (!lhs->isDummy())
				lhs->parent = n->parent;
		}
	public:

		iterator erase(iterator pos)
		{
			node_type *n = pos.base();
			iterator next = ++pos;

			// If the position we're trying to erase is end(), return
			if (n->isDummy())
				return pos;

			// If it only has one node, or it has no child nodes
			if (n->right->isDummy())
			{
				erase_helper(n, n->left);

				// Fix nil node
				if (m_nil_node->parent == n && !n->left->isDummy())
					m_nil_node->parent = n->left;
				else if (m_nil_node->parent == n)
					m_nil_node->parent = n->parent;
			}
			else if (n->left->isDummy())
			{
				erase_helper(n, n->right);

				// Fix nil node
				if (m_nil_node->parent == n)
					m_nil_node->parent = n->right;
			}

			// if it has 2 children
			else
			{
				node_type *rl = n->right->left_most();

				// detach rl
				if (rl->parent->left == rl)
				{
					rl->parent->left = rl->right;
					if (!rl->right->isDummy())
						rl->right->parent = rl->parent;
				}
				else
				{
					rl->parent->right = rl->right;
					if (!rl->right->isDummy())
						rl->right->parent = rl->parent;
				}

				// Set rl to n
				rl->parent = n->parent;
				rl->left = n->left;
				rl->right = n->right;

				// Detach n
				if (n->parent)
				{
					if (n->parent->left == n)
						n->parent->left = rl;
					else
						n->parent->right = rl;
				}
				else
					m_root = rl;

				// Fix rl's (n) children
				if (!rl->left->isDummy())
					rl->left->parent = rl;
				if (!rl->right->isDummy())
					rl->right->parent = rl;
			}

			// destroy and deallocate N
			--m_size;
			m_alloc.destroy(n);
			m_alloc.deallocate(n, 1);
			return next;
		}

		void swap(BST& other)
		{
			size_type			tmp_size = other.m_size;
			allocator_type		tmp_alloc = other.m_alloc;
			node_type*			tmp_root = other.m_root;
			node_type*			tmp_nil_node = other.m_nil_node;

			other.m_size = m_size;
			m_size = tmp_size;

			other.m_alloc = m_alloc;
			m_alloc = tmp_alloc;

			other.m_root = m_root;
			m_root = tmp_root;

			other.m_nil_node = m_nil_node;
			m_nil_node = tmp_nil_node;
		}

		// lookup
		iterator find(const key_type& key)
		{
			node_type *n = m_root;
			while (!n->isDummy() && n->value.first != key)
				n = m_comp(key, n->value.first) ? n->left : n->right;
			return iterator(n);
		}
		const_iterator find(const key_type& key) const
		{
			const node_type *n = m_root;
			while (!n->isDummy() && n->value.first != key)
				n = m_comp(key, n->value.first) ? n->left : n->right;
			return const_iterator(n);
		}

		iterator lower_bound(const key_type& k)
		{
			node_type *n = m_root;
			node_type *t = m_root; // top result so far

			if (n->isDummy())
				return (iterator(n));
			// If the key is more than rightmost, return end
			if (m_comp(m_root->right_most()->value.first, k))
				return end();

			while (!n->isDummy())
			{
				n = (!m_comp(k, n->value.first)) ? n->right : n->left;
				if (m_comp(t->value.first, k) || (!n->isDummy() && m_comp(n->value.first, t->value.first)
												   && !m_comp(n->value.first, k)))
					t = n;
			}
			return (iterator(t));
		}

		const_iterator lower_bound(const key_type& k) const
		{
			const node_type *n = m_root;
			const node_type *t = m_root; // top result so far

			if (n->isDummy())
				return (const_iterator(n));
			// If the key is more than rightmost, return end
			if (m_comp(m_root->right_most()->value.first, k))
				return end();

			while (!n->isDummy())
			{
				n = (!m_comp(k, n->value.first)) ? n->right : n->left;
				if (m_comp(t->value.first, k) || (!n->isDummy() && m_comp(n->value.first, t->value.first)
												   && !m_comp(n->value.first, k)))
					t = n;
			}
			return (const_iterator(t));
		}
		iterator upper_bound(const key_type& k)
		{
			node_type *n = m_root;
			node_type *t = m_root; // top result so far

			if (n->isDummy())
				return (iterator(n));
			// If the key is more than rightmost, return end
			if (m_comp(m_root->right_most()->value.first, k))
				return end();

			while (!n->isDummy())
			{
				n = (!m_comp(k, n->value.first)) ? n->right : n->left;
				if (!m_comp(k, t->value.first) || (!n->isDummy() && m_comp(n->value.first, t->value.first)
												   && m_comp(k, n->value.first)))
					t = n;
			}
			return (iterator(t));
		}

		const_iterator upper_bound(const key_type& k) const
		{
			const node_type *n = m_root;
			const node_type *t = m_root; // top result so far

			if (n->isDummy())
				return (const_iterator(n));
			// If the key is more than rightmost, return end
			if (m_comp(m_root->right_most()->value.first, k))
				return end();

			while (!n->isDummy())
			{
				n = (!m_comp(k, n->value.first)) ? n->right : n->left;
				if (!m_comp(k, t->value.first) || (!n->isDummy() && m_comp(n->value.first, t->value.first)
												   && m_comp(k, n->value.first)))
					t = n;
			}
			return (const_iterator(t));
		}

		node_type* base()				{ return m_root; }
		const node_type* base() const	{ return m_root; }
		allocator_type get_allocator() const { return m_alloc; }
	};
}



#endif
