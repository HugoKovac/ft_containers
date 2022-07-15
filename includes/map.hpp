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

/*
		void _insert_case4(Node *n){
			if (n == n->parent->right && n->parent == _grandpa(n)->left){
				_rotate_left(n->parent);
				n = n->left;
			}
			else
				_insert_case5(n);
		}

		void _insert_case3(Node *n){
			if (_uncle(n) && _uncle(n)->color == RED){
				n->parent->color = BLACK;
				_uncle(n)->color = BLACK;
				_grandpa(n)->color = RED;
				_insert_case1(_grandpa(n));
			}
			else
				_insert_case4(n);
		}

		void _insert_case2(Node *n){
			if (n->parent->color == BLACK)
				return;
			_insert_case3(n);
		}

		void _insert_case1( Node *n){
			if (!n->parent)
				n->color = BLACK;
			else
				_insert_case2(n);
		}


		void _insert_case5(Node *n){
			n->parent->color = BLACK;
			_grandpa(n)->color = RED;
			if (n == n->parent->left && n->parent == _grandpa(n)->left)
				_rotate_right(_grandpa(n));
			else
			{
				if (n == n->parent->right && n->parent == _grandpa(n)->right)
					_rotate_left(_grandpa(n));
			}
		}
*/
	public :
		Tree(const key_compare& comp, const allocator_type& alloc) :
		_root(NULL),
		_size(0),
		_comp(comp),
		_alloc_node(alloc){}

		Tree(Tree const &src) : _root(NULL), _comp(src._comp), _alloc_node(src._alloc_node){}

		~Tree(){ clear(_root); }

		Node *newNode(value_type const &val/*, color_type new_color*/){
			return new Node(val, /*new_color,*/ _alloc_node);
		}

		void clear1(){ clear(_root); _root = NULL; }

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

		/*pair<iterator,bool> insert(value_type const &val)//?change return type
		{
			Node *inserted_node = new Node(val, RED, _alloc_node);
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
			_insert_case1(inserted_node);
			return make_pair(iterator(inserted_node, _root), true);
		}*/

		pair<iterator,bool> insert(value_type const &val){
			std::cout << "=========" << std::endl;
			std::cout << val.first << std::endl;
			std::cout << val.second << std::endl;
			std::cout << "=========" << std::endl;
			Node *insertNode = new Node(val, _alloc);
			Node *y = NULL;
			Node *temp = _root;
			while(temp != NULL) {
			y = temp;
			if(_comp(insertNode->value->first, temp->value->first))
				temp = temp->left;
			else
				temp = temp->right;
			}
			insertNode->parent = y;

			if(y == NULL)
				_root = insertNode;
			else if(_comp(insertNode->value->first, y->value->first))
				y->left = insertNode;
			else
				y->right = insertNode;
			return make_pair(iterator(insertNode, _root), true);
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

		Node *find (const value_type& val){//! val passe par erase range seg.fault
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
			- w le frere de x
			(dans le cas ou z a 1 ou 0 fils : x remplace z. (y = z))
		*/
		// void FixRules(Node *x){//!verif les NULL possibles
		// 	if (x){
		// 		while (x != _root && x->color == BLACK){//en cas de double noir de x et !_root
		// 			if (x == x->parent->left){//cas ou x est a gauche
		// 				Node *w = x->parent->right;
		// 				if (w){
		// 					if(w->color == RED) {//case1
		// 						w->color = BLACK;
		// 						x->parent->color = RED;
		// 						_rotate_left(x->parent);
		// 						w = x->parent->right;
		// 					}
		// 					if(w->left && w->left->color == BLACK && w->right && w->right->color == BLACK) {//case2
		// 						w->color = RED;
		// 						x = x->parent;
		// 					}
		// 					else {
		// 						if(w->right && w->right->color == BLACK) {//case 3
		// 							if (w->left)
		// 								w->left->color = BLACK;
		// 							w->color = RED;
		// 							_rotate_right(w);
		// 							w = x->parent->right;
		// 						}//case 3 et 4
		// 						w->color = x->parent->color;
		// 						x->parent->color = BLACK;
		// 						if (w->right)
		// 							w->right->color = BLACK;
		// 						_rotate_left(x->parent);
		// 						x = _root;
		// 					}
		// 				}
		// 				else
		// 					break ;
		// 			}
		// 			else{//cas ou x est a droite
		// 				Node *w = x->parent->left;
		// 				if (w){
		// 					if(w->color == RED) {//case1
		// 						w->color = BLACK;
		// 						x->parent->color = RED;
		// 						_rotate_right(x->parent);
		// 						w = x->parent->left;
		// 					}
		// 					if(w->right && w->right->color == BLACK && w->left && w->left->color == BLACK) {//case2
		// 						w->color = RED;
		// 						x = x->parent;
		// 					}
		// 					else {
		// 						if(w->left && w->left->color == BLACK) {//case 3
		// 							if (w->right)
		// 								w->right->color = BLACK;
		// 							w->color = RED;
		// 							_rotate_left(w);
		// 							w = x->parent->left;
		// 						}//case 3 et 4
		// 						w->color = x->parent->color;
		// 						x->parent->color = BLACK;
		// 						if (w->left)
		// 							w->left->color = BLACK;
		// 						_rotate_right(x->parent);
		// 						x = _root;
		// 					}
		// 				}
		// 				else
		// 					break;
		// 			}
		// 		}
		// 		x->color = BLACK;//remis a la bonne couleur
		// 	}
		// }

		bool del(Node *z) {
			Node *y = z;//Pour le cas de z == 0 ou 1 enfant
			Node *x;
			// color_type org_color_y = y->color;//va etre la couleur de x, pour savoir si double noir a la fin

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
			// if (org_color_y == BLACK)//x = noir noir ou noir rouge
			// 	FixRules(x);//corriger les violation de rule de RBT
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
				if (_comp(it->first, val.first) == true)
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
		///END CONSTRUCTORS///

		map& operator= (const map& x){ insert(x.begin(), x.end()); return *this; }

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

		// void swap (map& x){
		// 	map<key_type, mapped_type> save;
		// 	save = x;
		// 	std::cout << "x => " << x.begin()->first << std::endl;
		// 	std::cout << "save de this => " << save.begin()->first << std::endl;
		// 	std::cout << "x => " << x.begin()->first << std::endl;
		// 	x = *this;
		// 	*this = save;
		// 	std::cout << "save de this=> " << save.begin()->first << std::endl;
		// 	std::cout << "this => " << this->begin()->first << std::endl;
		// }

		void clear() { _rbt.clear1(); }

		void erase (iterator position){ _rbt.erase(position); }
		size_type erase (const key_type& k){ return _rbt.erase(make_pair(k, 0)); }
		void erase (iterator first, iterator last){ _rbt.erase_it(first, last); }

		iterator lower_bound (const key_type& k){ return _rbt.lower_bound(make_pair(k, 0)); }
		const_iterator lower_bound (const key_type& k) const{ return _rbt.lower_bound(make_pair(k, 0)); }

		iterator upper_bound (const key_type& k){ return _rbt.upper_bound(make_pair(k, 0)); }
		const_iterator upper_bound (const key_type& k) const{ return _rbt.upper_bound(make_pair(k, 0)); }
	};
}
#endif // MAP_HPP