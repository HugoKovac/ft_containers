#if !defined(MAP_HPP)
#define MAP_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterator.hpp"

#define BLACK true
#define RED false

namespace ft{
	template < class T, class Compare, class Alloc > 
	class Tree{
	public :
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef Compare											compare_type;
		typedef typename allocator_type::reference 				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::size_type				size_type;

		struct Node{
			// typedef bool color_type;

			// color_type color;
			Node *parent;
			Node *left;
			Node *right;
			value_type *value;
			allocator_type alloc;

			Node(const allocator_type& alloc)
			: /*color(RED),*/ parent(NULL), left(NULL), right(NULL), value(NULL), alloc(alloc){}

			Node(value_type const &val, /*color_type new_color,*/ const allocator_type& alloc)
			: /*color(new_color),*/ parent(NULL), left(NULL), right(NULL), value(NULL), alloc(alloc){
				value = this->alloc.allocate(1);
				this->alloc.construct(value, val);
			}

			~Node(){ alloc.deallocate(value, 1); }
		};


		typedef MapIter<Node, value_type>						iterator;
		typedef MapIter<Node, const value_type>					const_iterator;
		typedef RevIter<iterator>								reverse_iterator;
		typedef RevIter<const iterator>							const_reverse_iterator;

	private :
		typedef typename Alloc::template rebind< Node >::other	allocator_type_node;
		// typedef bool color_type;

		Node	*_root;
		size_type _size;
		compare_type _comp;
		allocator_type _alloc_node;
		allocator_type_node _alloc;
		bool _cpy;

		Node *_min(Node *n) const{
			Node *tmp;
			tmp = n;

			while (tmp && tmp->left)
				tmp = tmp->left;
		
			return tmp;
		}

		Node *_max(Node *n) const{
			Node *tmp;
			tmp = n;

			while (tmp && tmp->right)
				tmp = tmp->right;
		
			return tmp;
		}
		
		Node *_sibling(Node *n) const{
			if (n && n->parent && n->parent->left && n->parent->right){
				if (n->parent->left == n)
					return n->parent->right;
				else
					return n->parent->left;
			}
			return NULL;
		}

		Node *_uncle(Node *n) const{
			if (n && n->parent)
				return _sibling(n->parent);
			return NULL;
		}

		Node *_grandpa(Node *n) const{
			if (n && n->parent && n->parent->parent){
				return n->parent->parent;
			}
			return NULL;
		}

		void _replace_node(Node *oldNode, Node *newNode)
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

		void _rotate_left(Node *x){
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

		void _rotate_right(Node *x)
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

	public :
		Tree(const key_compare& comp, const allocator_type& alloc) :
		_root(NULL),
		_size(0),
		_comp(comp),
		_alloc_node(alloc),
		_cpy(false){}

		Tree(Tree const &src) : _root(NULL), _comp(src._comp), _alloc_node(src._alloc_node), _cpy(false){}

		~Tree(){ if (!_cpy) clear1(); }

		Tree& operator= (const Tree& x){
			_root = x._root;
			_size = x._size;
			_comp = x._comp;
			_alloc_node = x._alloc_node;
			_cpy = true;
			return *this;
		}
		
		Node *newNode(value_type const &val/*, color_type new_color*/){
			return new Node(val, /*new_color,*/ _alloc_node);
		}

		void clear1(){ 
			if (!_cpy)
				clear(_root);
		 	_root = NULL; 
			_cpy = false;
		}

		void clear(Node *n){
			if (n == NULL)
					return ;
			if (n->right != NULL)
				clear(n->right);
			if (n->left != NULL)
				clear(n->left);
			--_size;
			this->_alloc.destroy(n);
			this->_alloc.deallocate(n, 1);
		}

		pair<iterator,bool> insert(value_type const &val)
		{
			Node *inserted_node = new Node(val, _alloc_node);
			if (!_root){
				_root = inserted_node;
				++_size;
			}
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
					else if (_comp(n->value->first, val.first))
					{
						if (n->right == NULL)
						{
							n->right = inserted_node;
							break;
						}
						else
							n = n->right;
					}
					else if(!_comp(val.first, n->value->first) && !_comp(n->value->first, val.first)){
						delete inserted_node;
						return make_pair(iterator(n, _root), true);
					}
				}
				++_size;
				inserted_node->parent = n;
			}
			return make_pair(iterator(inserted_node, _root), true);
		}

		size_type size() const{ return _size; }

		bool empty() const{ return _size == 0; }

		iterator begin(){ return iterator(_min(_root), _root); }
		const_iterator begin() const{ return const_iterator(_min(_root), _root); }

		iterator end(){ return iterator(NULL, _root); }
		const_iterator end() const{ return const_iterator(NULL, _root); }

		reverse_iterator rbegin(){ return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const{ return const_reverse_iterator(end()); }

		reverse_iterator rend(){ return reverse_iterator(begin()); }
		const_reverse_iterator rend() const{ return const_reverse_iterator(begin()); }

		size_type max_size() const{ return _alloc.max_size(); }

		Node *find (const value_type& val){
			if (!_root)
				return NULL;
			else
			{
				Node *n = _root;
				while (1)
				{
					if (_comp(val.first, n->value->first))
					{
						if (n->left == NULL)
							return NULL;
						else
							n = n->left;
					}
					else if (_comp(n->value->first, val.first))
					{
						if (n->right == NULL)
							return NULL;
						else
							n = n->right;
					}
					else if(!_comp(val.first, n->value->first) && !_comp(n->value->first, val.first)){
						if (!n)
							return NULL;
						return n;
					}
				}
			}
		}

		iterator find_inter (const value_type& val){ return iterator(find(val), _root); }

		Node *find (const value_type& val) const{
			if (!_root)
				return NULL;
			else
			{
				Node *n = _root;
				while (1)
				{
					if (_comp(val.first, n->value->first))
					{
						if (n->left == NULL)
							return NULL;
						else
							n = n->left;
					}
					else if (_comp(n->value->first, val.first))
					{
						if (n->right == NULL)
							return NULL;
						else
							n = n->right;
					}
					else if(!_comp(val.first, n->value->first) && !_comp(n->value->first, val.first)){
						if (!n)
							return NULL;
						return n;
					}
				}
			}
		}

		const_iterator find_inter (const value_type& val)const{ return const_iterator(find(val), _root); }

		void Transplant(Node *z, Node *x){//x peut etre NULL
			if (!z->parent)//z == _root
				_root = x;
			else if (z == z->parent->left)
				z->parent->left = x;
			else
				z->parent->right = x;
			if (x)//si x !NULL
				x->parent = z->parent;
		}

		/*(https://www.codesdope.com/course/data-structures-red-black-trees-deletion/)
			Soit : 
			- z le node a supprimer
			- y le node qui remplace z
			- x le node qui remplace y
			(dans le cas ou z a 1 ou 0 fils : x remplace z. (y = z))
		*/

		bool del(Node *z) {
			Node *y = z;//Pour le cas de z == 0 ou 1 enfant
			Node *x;
			// color_type org_color_y = y->color;//va etre la couleur de x, pour savoir si double noir a la fin

			if (z == _root)
				_cpy = false;
			if (!z->left){//si !left donc 1 ou 0 enfant
				x = z->right;//l'enfant qui va replace z est right (soit Node* soit NULL)
				Transplant(z, z->right);//on remplace z par x dans l'arbre
			}
			else if (!z->right){//si !right donc 1 ou 0 enfant
				x = z->left;//l'enfant qui va replace z est left (soit Node* soit NULL)
				Transplant(z, z->left);//on remplace z par x dans l'arbre
			}
			else{//z a 2 enfants
				y = _min(z->right);//l'ordre de l'arbre est repecté
				// org_color_y = y->color;
				x = y->right;//l'ordre de l'arbre est repecté, x peut etre NULL
				if (y->parent == z){//y est enfant direct de z
					if (x)
						x->parent = y;
				}
				else{//y n'est pas enfant direct de z
					Transplant(y, y->right);//on remplace y par x dans l'arbre mais la var y est tjs y
					y->right = z->right;//y est decroché et on le recontruit avant de transplant
					y->right->parent = y;//pour montrer que y est indépendant. y->right pas null car = a z->right
				}
				Transplant(z, y);//transplantation de y dans l'arbre a la place de z
				y->left = z->left;//reprise des caracteristique de z
				y->left->parent = y;//reprise des caracteristique de z
				// y->color = z->color;//reprise des caracteristique de z
			}
			return true;
		}

		void erase(iterator position) {
			Node *n = NULL;
			if (position != end())
				n = find(*position);
			if (n)
				del(n);
		}

		size_type erase (const value_type& val){
			Node *n = find(val);
			if (n)
				return del(n) == true ? 1 : 0;
			return 0;
		}
		void erase_it (iterator first, iterator last){
			while (first != last){
				erase(first);
				first++;
			}
		}

		iterator lower_bound (const value_type& val){
			iterator it = begin();
			for (; it != end(); ++it)
				if (_comp(it->first, val.first) == false)
					break ;
			return (it);
		}

		const_iterator lower_bound (const value_type& val)const{
			const_iterator it = begin();
			for (; it != end(); ++it)
				if (_comp(it->first, val.first) == false)
					break ; 
			return (it);
		}

		iterator upper_bound (const value_type& val){
			iterator it = begin();
			for (; it != end(); ++it)
				if (_comp(val.first, it->first) == true)
					break ;
			return (it);
		}

		const_iterator upper_bound (const value_type& val)const{
			const_iterator it = begin();
			for (; it != end(); ++it)
				if (_comp(it->first, val.first) == true)
					break ;
			return (it);
		}

		void swap(Tree &x){
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
			std::swap(_alloc_node, x._alloc_node);
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
		typedef Tree<value_type, Compare, Alloc>			Tree_alias;
		///END TYPEDEFS///

	private:
		Tree_alias _rbt;
		key_compare _tree_comp;
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
		typedef typename Tree_alias::iterator						iterator;
		typedef typename Tree_alias::const_iterator					const_iterator;
		typedef typename Tree_alias::reverse_iterator				reverse_iterator;
		typedef typename Tree_alias::const_reverse_iterator			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;
		///END TYPEDEFS CONTINUATION///
	private:
		allocator_type _node_alloc;
	public:
		///CONSTRUCTORS///
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbt(comp, alloc){}
		
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _rbt(comp, alloc){
			insert(first, last);
		}

		map (const map& x) : _rbt(x._rbt){ this->insert(x.begin(), x.end()); }

		~map(){ }

		///END CONSTRUCTORS///

		map& operator= (const map& x){ _rbt = x._rbt; return *this; }

		iterator begin(){ return _rbt.begin(); }
		const_iterator begin() const{ return _rbt.begin(); }

		reverse_iterator rbegin(){ return _rbt.rbegin(); }
		const_reverse_iterator rbegin() const{ return _rbt.rbegin(); }

		iterator end(){ return _rbt.end(); }
		const_iterator end() const{ return _rbt.end(); }

		reverse_iterator rend(){ return _rbt.rend(); }
		const_reverse_iterator rend() const{ return _rbt.rend(); }

		pair<iterator,bool> insert (const value_type& val){ return _rbt.insert(val); }

		iterator insert (iterator position, const value_type& val){ static_cast<void>(position); insert(val); }

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		size_type size() const{ return _rbt.size(); }

		bool empty() const{ return _rbt.empty(); }

		size_type max_size() const{ return _rbt.max_size(); }

		mapped_type& operator[] (const key_type& k){ return (*((insert(make_pair(k,mapped_type()))).first)).second; }

		value_compare value_comp() const{ return value_compare(); }
		key_compare key_comp() const{ return key_compare(); }
		allocator_type get_allocator() const{ return allocator_type(); }

		iterator find (const key_type& k){ return _rbt.find_inter(make_pair(k, 0)); }
		const_iterator find (const key_type& k) const{ return _rbt.find_inter(make_pair(k, 0)); }

		size_type count (const key_type& k) const{ return find(k) != end(); }

		void swap (map& x){ _rbt.swap(x._rbt); }

		void clear() { _rbt.clear1(); }

		void erase (iterator position){ _rbt.erase(position); }
		size_type erase (const key_type& k){ return _rbt.erase(make_pair(k, 0)); }
		void erase (iterator first, iterator last){ _rbt.erase_it(first, last); }

		iterator lower_bound (const key_type& k){ return _rbt.lower_bound(make_pair(k, 0)); }
		const_iterator lower_bound (const key_type& k) const{ return _rbt.lower_bound(make_pair(k, 0)); }

		iterator upper_bound (const key_type& k){ return _rbt.upper_bound(make_pair(k, 0)); }
		const_iterator upper_bound (const key_type& k) const{ return _rbt.upper_bound(make_pair(k, 0)); }

		pair<iterator, iterator> equal_range (const key_type& k) { return (ft::make_pair(lower_bound(k), upper_bound(k))); }
		pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k))); }
	};
}
#endif // MAP_HPP