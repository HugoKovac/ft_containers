#if !defined(MAP_HPP)
#define MAP_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterator.hpp"
#include <iostream>//!remove

#define BLACK true
#define RED false

namespace ft{
	template < class T, class Compare, class Alloc > 
	class Tree{
	public :
		typedef T											value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef Compare										compare_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;

		struct Node{
			typedef bool color_type;

			color_type color;
			Node *parent;
			Node *left;
			Node *right;
			value_type *value;
			allocator_type alloc;

			Node() : color(RED), parent(NULL), left(NULL), right(NULL), value(NULL){}

			Node(value_type const &val, color_type new_color) : color(new_color), parent(NULL), left(NULL), right(NULL), value(NULL){
				value = alloc.allocate(1);
				alloc.construct(value, val);
			}
		};

		typedef MapIter<Node, value_type>							iterator;
		typedef MapIter<Node, const value_type>					const_iterator;

	private :
		typedef bool color_type;

		Node	*_root;
		size_type _size;
		compare_type _comp;

		Node *_min(Node *n){
			Node *tmp;
			tmp = n;

			while (tmp && tmp->left)
				tmp = tmp->left;
		
			return tmp;
		}

		Node *_max(Node *n){
			Node *tmp;
			tmp = n;

			while (tmp && tmp->right)
				tmp = tmp->right;
		
			return tmp;
		}
		
		Node *sibling(Node *n){
			if (n && n->parent && n->parent->left && n->parent->right){
				if (n->parent->left == n)
					return n->parent->right;
				else
					return n->parent->left;
			}
			return NULL;
		}

		Node *uncle(Node *n)
		{
			if (n && n->parent)
				return sibling(n->parent);
			return NULL;
		}

		Node *grandpa(Node *n){
			if (n && n->parent && n->parent->parent){
				return n->parent->parent;
			}
			return NULL;
		}

		void replace_node(Node *oldNode, Node *newNode)
		{
			if (oldNode->parent == NULL)
				_root = newNode;
			else
			{
				if (oldNode == oldNode->parent->left)
					oldNode->parent->left = newNode;
				else
					oldNode->parent->right = newNode;
			}
			if (newNode != NULL)
				newNode->parent = oldNode->parent;
		}

		void rotate_left(Node *x){
			Node *y = x->right;
			x->right = y->left;
			if (y->left) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (!x->parent) {
				_root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void rotate_right(Node *x)
		{
			Node *y = x->left;
			x->left = y->right;
			if (y && y->right) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (!x->parent) {
				_root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}


		void insert_case4(Node *n){
			if (n == n->parent->right && n->parent == grandpa(n)->left){
				rotate_left(n->parent);
				n = n->left;
			}
			else
				insert_case5(n);
		}

		void insert_case3(Node *n){
			if (uncle(n) && uncle(n)->color == RED){
				n->parent->color = BLACK;
				uncle(n)->color = BLACK;
				grandpa(n)->color = RED;
				insert_case1(grandpa(n));
			}
			else
				insert_case4(n);
		}

		void insert_case2(Node *n){
			if (n->parent->color == BLACK)
				return;
			insert_case3(n);
		}

		void insert_case1( Node *n){
			if (!n->parent)
				n->color = BLACK;
			else
				insert_case2(n);
		}


		void insert_case5(Node *n){
			n->parent->color = BLACK;
			grandpa(n)->color = RED;
			if (n == n->parent->left && n->parent == grandpa(n)->left)
				rotate_right(grandpa(n));
			else
			{
				if (n == n->parent->right && n->parent == grandpa(n)->right)
					rotate_left(grandpa(n));
			}
		}

	public :
		Tree() : _root(NULL), _size(0){}

		Node *newNode(value_type const &val, color_type new_color){
			return new Node(val, new_color);
		}

		void insert(value_type const &val)//?change return type
		{
			Node *inserted_node = new Node(val, RED);
			if (!_root)
				_root = inserted_node;
			else
			{
				Node *n = _root;
				while (1)
				{
					if (_comp(val.first, n->value->first))
					{
						if (n->left == NULL)
						{
							n->left = inserted_node;
							break;
						}
						else
							n = n->left;
					}
					else if (!_comp(val.first, n->value->first))
					{
						if (n->right == NULL)
						{
							n->right = inserted_node;
							break;
						}
						else
							n = n->right;
					}
					else{
						n->value->second = val.second;
						delete inserted_node;
						return;
					}
				}
				inserted_node->parent = n;
			}
			insert_case1(inserted_node);
			// verify_properties(t);
		}

		iterator begin(){ return iterator(_min(_root)); }
		const_iterator begin() const{ return const_iterator(_min(_root)); }

		iterator end(){ return iterator(_max(_root)); }
		const_iterator end() const{ return const_iterator(_max(_root)); }

	};

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map{
	public:
		///TYPEDEFS///
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const Key,T>							value_type;
		typedef Compare										key_compare;
		typedef Tree<value_type, Compare, Alloc>				Tree;
		///END TYPEDEFS///

	private:
		Tree _rbt;
		///MEMBER CLASS VALUE_CMP///
		class value_compare : public std::binary_function<value_type,value_type,bool>
		{
		friend class map;
		protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		///END MEMBER CLASS VALUE_CMP///

	public:
		///TYPEDEFS CONTINUATION///
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename Tree::iterator								iterator;
		typedef typename Tree::const_iterator						const_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;
		///END TYPEDEFS CONTINUATION///

		iterator begin(){ return _rbt.begin(); }

		const_iterator begin() const{ return _rbt.begin(); }

		iterator end(){ return _rbt.end(); }

		const_iterator end() const{ return _rbt.end(); }

		void insert (const value_type& val)//!change return type
		{
			_rbt.insert(val);
		}
	};

}
#endif // MAP_HPP