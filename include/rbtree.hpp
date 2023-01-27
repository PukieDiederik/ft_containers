#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include <functional>
#include <memory>

namespace ft
{
	template<typename T>
	struct _TreeNode
	{
		T value;

		_TreeNode* parent;
		_TreeNode* left;
		_TreeNode* right;

		_TreeNode() : parent(NULL), left(NULL), right(NULL) { }
		_TreeNode(const T& _value, _TreeNode* _parent, _TreeNode* _left, _TreeNode* _right)
			: value(_value), parent(_parent), left(_left), right(_right) { }
		_TreeNode(_TreeNode* _parent) :parent(_parent), left(NULL), right(NULL) { }


		_TreeNode* left_most()
		{
			_TreeNode* tmp = this;
			for (; tmp->left != NULL; tmp = tmp->left);
			return tmp;
		}
		_TreeNode* right_most()
		{
			_TreeNode* tmp = this;
			for (; tmp->right != NULL; tmp = tmp->right);
			return tmp;
		}

		inline bool isDummy() { return (!left && !right); }
	};

	template <typename T, typename Compare = std::less<T>, typename EqualsCompare = std::equal_to<T>,
			  typename Allocator = std::allocator<_TreeNode<T> > >
	class RedBlackTree
	{
	private:
		template<typename Base>
		class _iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
		{
		protected:
			Base m_base;


		public:
			//constructors
			_iterator() : m_base(NULL) { }
			_iterator(Base base) : m_base(base) { }
			_iterator(const _iterator& copy) : m_base(copy) { }

			~_iterator() { }

			_iterator& operator=(const _iterator& copy) { m_base = copy.m_base; }


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
		typedef T				value_type;
		typedef _TreeNode<T>	node_type;
		typedef Compare			compare_type;
		typedef EqualsCompare	equals_to_type;
		typedef Allocator		allocator_type;

		// TODO: difference types
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

		typedef _iterator<_TreeNode<T>* >				iterator;
		typedef _iterator<const _TreeNode<T>* >			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;



	private:
		size_type m_size;
		Allocator m_alloc;
		node_type *m_root;

	public:
		// Constructors/Destructors
		RedBlackTree() :m_root(new node_type(NULL)), m_alloc(Allocator()), m_size(0) { }
		explicit RedBlackTree(const Compare& comp, const Allocator& alloc = Allocator());
		// TODO: iterator constructor
		RedBlackTree(const RedBlackTree& copy);

		~RedBlackTree();

		iterator begin() { return iterator(m_root->left_most()); }
		const_iterator begin() const { return const_iterator(m_root->left_most()); }
		iterator end() { return iterator(NULL); }
		const_iterator end() const { return const_iterator(NULL); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator (end()); }
		reverse_iterator rend() {return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const { return m_size == 0; }
		size_type size() const { return m_size; }
		size_type max_size() const { return m_alloc.max_size(); }

		// modifiers
		void clear();

		ft::pair<iterator, bool> insert(const value_type& value);
		template<typename InputIt>
		void insert(InputIt first, InputIt last);

		void erase(iterator pos);
		void erase(iterator first, iterator last);

		void swap(RedBlackTree& other);

		// lookup
		iterator find(const value_type& v);
		const_iterator find(const value_type& v) const;

		iterator lower_bound(const value_type& v);
		iterator higher_bound(const value_type& v);

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

	template <typename T, typename Compare = std::less<T>, typename EqualsCompare = std::equal_to<T>, typename Allocator = std::allocator<T>>
	void swap(typename ft::RedBlackTree<T, Compare, EqualsCompare, Allocator>& lhs,
			  typename ft::RedBlackTree<T, Compare, EqualsCompare, Allocator>& rhs)
	{ lhs.swap(rhs); }
}



#endif
