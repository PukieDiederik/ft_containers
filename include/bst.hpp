#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <functional>
#include <memory>
#include <iostream>

namespace ft
{
	template<typename T>
	struct _TreeNode
	{
		T* value;

		_TreeNode* parent;
		_TreeNode* left;
		_TreeNode* right;

		_TreeNode() : value(NULL), parent(NULL), left(NULL), right(NULL) { }
		_TreeNode(_TreeNode* _parent) :value(NULL), parent(_parent), left(NULL), right(NULL) { }
		_TreeNode(const _TreeNode& copy) :value(copy.value), parent(copy.parent), left(copy.left), right(copy.right) { }

		_TreeNode<T>& operator=(const _TreeNode<T>& copy)
		{
			value = copy.value;
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
		}

		_TreeNode* left_most()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->left->isDummy()) ? tmp->right : tmp->left;
			return tmp;
		}
		_TreeNode* right_most()
		{
			_TreeNode* tmp = this;
			while (!tmp->isDummy() && !tmp->isLeaf())
				tmp = (tmp->right->isDummy()) ? tmp->left : tmp->right;
			return tmp;
		}

		inline bool isDummy() { return (!left && !right); }
		inline bool isLeaf() { return !(left->isDummy() || right->isDummy()); }
	};

	template <typename Key, typename T,
			  typename Compare = std::less<Key>,
			  typename Allocator = std::allocator<ft::pair<Key, T> >,
			  typename NodeAllocator = std::allocator<_TreeNode<ft::pair<Key, T> > > >
	class BST
	{
	public:
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef ft::pair<Key, T>	value_type;
		typedef Compare				value_compare;
		typedef Allocator			allocator_type;

	private:
		template<typename Base>
		class _iterator : public ft::iterator<std::bidirectional_iterator_tag, value_type>
		{
		private:
			typedef ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, value_type> > m_traits;
		protected:
			Base m_base;

		public:
			//typedefs
			typedef typename m_traits::value_type			value_type;
			typedef typename m_traits::difference_type		difference_type;
			typedef typename m_traits::pointer				pointer;
			typedef typename m_traits::reference			reference;
			typedef typename m_traits::iterator_category	iterator_category;

			//constructors
			_iterator() : m_base(NULL) { }
			_iterator(Base base) : m_base(base) { }
			_iterator(const _iterator& copy) : m_base(copy.m_base) { }

			~_iterator() { }

			_iterator& operator=(const _iterator& copy) { m_base = copy.m_base; return *this;}


			_iterator& operator++()
			{
				if (m_base->right->isDummy())
					m_base = m_base->parent;
				else
				{
					m_base = m_base->parent->right;
					if (!m_base->isDummy())
						return *this;
					for (; !m_base->left->isDummy(); m_base = m_base->left);
				}
				return *this;
			}
			_iterator& operator++(int)
			{
				Base tmp = m_base;
				operator++();
				return tmp;
			}

			_iterator& operator--()
			{
				if ((m_base->left->isDummy() && m_base->right->isDummy()) || !m_base->right->isDummy())
					m_base = m_base->parent;
				else
				{
					m_base = m_base->left;
					for (; !m_base->right->isDummy(); m_base = m_base->right);
				}
				return *this;

			}
			_iterator& operator--(int)
			{
				Base tmp = m_base;
				operator--();
				return tmp;
			}

			const Base& base() const { return m_base; }
		};

	public:
		typedef _TreeNode<value_type>	node_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;


		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

		typedef _iterator<node_type*>				iterator;
		typedef _iterator<const node_type*>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;



	private:

		size_type 		m_size;
		Allocator 		m_alloc;
		NodeAllocator	m_node_alloc;
		const Compare 		m_comp;

		node_type* m_root;

		void add_value(node_type* n, const value_type& value)
		{
			n->value = m_alloc.allocate(1);
			m_alloc.construct(n->value, value);
			n->left = m_node_alloc.allocate(1);
			n->right = m_node_alloc.allocate(1);
			m_node_alloc.construct(n->left, node_type(n));
			m_node_alloc.construct(n->left, node_type(n));
		}

		void erase_helper(node_type *n, node_type *lhs, node_type *rhs)
		{
			//fixes parent
			if (n->parent)
			{
				if (n->parent->left == n)
					n->parent->left = lhs;
				else
					n->parent->right = lhs;
			}
			else // base is root in this case
				m_root = lhs;
			// removes dummy node
			m_node_alloc.destroy(rhs);
			m_node_alloc.deallocate(rhs);
			// removes base node
			m_node_alloc.destroy(n);
			m_node_alloc.deallocate(n);
		}

	public:
		// Constructors/Destructors
		explicit BST(Compare comp = Compare(), Allocator alloc = Allocator(), NodeAllocator nalloc = NodeAllocator())
			:m_size(0), m_alloc(alloc), m_node_alloc(nalloc), m_comp(comp), m_root(m_node_alloc.allocate(1))
		{
			m_node_alloc.construct(m_root, node_type(NULL));
		}
		// TODO: iterator constructor
		BST(const BST& copy) // TODO: copy constructor
			:m_size(copy.size()), m_alloc(copy.m_node_alloc), m_node_alloc(copy.m_node_alloc), m_comp(copy.m_comp)
		{
			(void)copy;
			m_root = m_node_alloc.allocate(1);
			m_node_alloc.construct(m_root, node_type(NULL));
		}

		~BST()
		{
			clear();
			m_node_alloc.destroy(m_root);
			m_node_alloc.deallocate(m_root, 1);
		}

		iterator begin() { return iterator(m_root->left_most()); }
		const_iterator begin() const { return const_iterator(m_root->left_most()); }
		iterator end() { return iterator(m_root->isDummy() ? m_root : m_root->right_most()->right); }
		const_iterator end() const { return const_iterator(m_root->isDummy() ? m_root : m_root->right_most()->right); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator (end()); }
		reverse_iterator rend() {return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const { return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }

		// modifiers
		void clear()
		{
			iterator n;
			if (m_root->isDummy())
				return ;
			for(iterator i = begin(), e = end(); i != e; i = n)
			{
				m_alloc.destroy(i.base()->value);
				m_node_alloc.destroy(i.base()->left);
				m_node_alloc.destroy(i.base()->right);
				m_node_alloc.deallocate(i.base()->left, 1);
				m_node_alloc.deallocate(i.base()->right, 1);
				n = i;
				++n;
			}
			m_root = m_node_alloc.allocate(1);
			m_node_alloc.construct(m_root, node_type(NULL));
			m_size = 0;
		}

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			// Basic BST insertion
			node_type* cur = m_root;
			while (!cur->isDummy() && cur->value.first != value.first)
			{
				if (m_comp(value.first, cur->value.first))
					cur = cur->left;
				else
					cur = cur->right;
			}
			if (cur->value.first == value.first)
				return ft::make_pair<iterator, bool>(iterator(cur), false);
			add_value(cur, value);
			++m_size;
			return ft::make_pair<iterator, bool>(iterator(cur), true);
		}

		void erase(iterator pos)
		{
			node_type* n = pos.base();

			if (n->isDummy())
				return;
			m_alloc.destroy(n->value);
			m_alloc.deallocate(n->value);
			// Case only 1 left node or no child nodes
			if (n->right->isDummy())
				erase_helper(n, n->left, n->right);
			// Case only right node exists
			else if (n->left->isDummy() && !n->right->isDummy())
				erase_helper(n, n->right, n->left);
			// Case both nodes exist
			else
			{
				node_type* rl = n->right->left_most();

				n->value = rl->value;
				erase_helper(rl, rl->left, rl->right);
			}
			--m_size;
		}

		void swap(BST& other)
		{
			size_type		tmp_size = other.m_size;
			Allocator		tmp_alloc = other.m_alloc;
			NodeAllocator	tmp_node_alloc = other.m_node_alloc;
			Compare 		tmp_comp = other.m_comp;
			node_type		*tmp_root = other.m_root;

			other.m_size = m_size;
			m_size = tmp_size;

			other.m_alloc = m_alloc;
			m_alloc = tmp_alloc;

			other.m_node_alloc = m_node_alloc;
			m_node_alloc = tmp_node_alloc;

			other.m_comp = m_comp;
			m_comp = tmp_comp;

			other.m_root = m_root;
			m_root = tmp_root;
		}

		// lookup
		iterator find(const key_type& key)
		{
			node_type *n = m_root;
			while (!n->isDummy() && n->value.first == key)
			{
				if (m_comp(key, n->value->first))
					n = n->left;
				else
					n = n->right;
			}
			if (n->isDummy())
				return end();
			return iterator(n);
		}
		const_iterator find(const key_type& key) const
		{
			const node_type *n = m_root;
			while (!n->isDummy() && n->value.first == key)
			{
				if (m_comp(key, n->value->first))
					n = n->left;
				else
					n = n->right;
			}
			if (n->isDummy())
				return end();
			return const_iterator(n);
		}

		//finds the first node not less than k.
		iterator lower_bound(const key_type& k)
		{
			node_type *n = m_root;
			node_type *t = NULL; // top result so far
			while (!n->isDummy())
			{
				if (m_comp(k, n->value->first))
				{
					if (!t || m_comp(n->value->first, t->value->first))
						t = n->value->first;
					n = n->left;
				}
				else
					n = n->right;
			}
			if (!t)
				return end();
			return (iterator(t));
		}
		const_iterator lower_bound(const key_type& k) const
		{
			const node_type *n = m_root;
			const node_type *t = NULL; // top result so far
			while (!n->isDummy())
			{
				if (m_comp(k, n->value->first))
				{
					if (!t || m_comp(n->value->first, t->value->first))
						t = n->value->first;
					n = n->left;
				}
				else
					n = n->right;
			}
			if (!t)
				return end();
			return (const_iterator(t));
		}
//		iterator upper_bound(const key_type& k);
//		const_iterator upper_bound(const key_type& k) const
//		{
//			const node_type *n = m_root;
//			const node_type *t = NULL; // top result so far
//			while (!n->isDummy())
//			{
//				if (comp(k, n->value->first))
//				{
//					if ((k != n->value->first) && !t || comp(n->value->first, t->value->first) )
//						t = n->value->first;
//					n = n->left;
//				}
//				else
//					n = n->right;
//			}
//			if (!t)
//				return end();
//			return (const_iterator(t));
//		}

		allocator_type get_allocator() const { return m_alloc; }

		// iterator
		template<typename IterL, typename IterR>
		friend bool operator==(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{
			return lhs.base() == rhs.base();
		}
		template<typename IterL, typename IterR>
		friend bool operator!=(const _iterator<IterL>& lhs, const _iterator<IterR>& rhs)
		{
			return lhs.base() != rhs.base();
		}
	};

	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(typename ft::BST<Key, T, Compare, Allocator>& lhs,
			  typename ft::BST<Key, T, Compare, Allocator>& rhs)
	{ lhs.swap(rhs); }
}



#endif
