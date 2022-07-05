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
		// allocator_type _alloc;
		size_type _size;
		compare_type _comp;
		

	public :
		Tree() : _root(NULL), _size(0){}

		Node *newNode(value_type const &val, color_type new_color){
			return new Node(val, new_color);
		}

		void insert(value_type const &val){//?change return type
			if (!_size)
				_root = newNode(val, BLACK);
		}

		iterator begin(){
			// if (!_root)
			// 	return iterator();
			Node *tmp;
			tmp = _root;
			while (tmp && tmp->left){
				tmp = tmp->left;
			}
		
			return iterator(tmp);
		}

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

		void insert (const value_type& val)//!change return type
		{
			_rbt.insert(val);
		}
	};

}
#endif // MAP_HPP