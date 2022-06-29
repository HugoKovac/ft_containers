#if !defined(MAP_HPP)
#define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"

#define BLACK 0
#define RED 1

namespace ft{
template < class Key,										// map::key_type
			class T,										// map::mapped_type
			class Compare = std::less<Key>,						// map::key_compare
			class Alloc = std::allocator<pair<const Key,T> >		// map::allocator_type
			> class map{

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef pair<const Key,T>							value_type;
	typedef Compare										key_compare;
	class value_compare : public std::binary_function<value_type, value_type, bool>
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
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference 			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	// typedef MapIter<value_type>							iterator;
	// typedef MapIter<const value_type>					const_iterator;
	// typedef MapRevIter<value_type>						reverse_iterator;
	// typedef MapRevIter<const value_type>				const_reverse_iterator;
	// typedef iterator_traits<iterator>					difference_type;

	struct _Node{
		char				color;
		pair<const Key,T>	pair;
		_Node				*next;

		_Node() : color(RED), pair(), next(NULL){}
		_Node(const Key key, T const data) : color(RED), pair(key, data), next(NULL){}
		_Node(const Key key, T const data, char color, T* next) : color(color), pair(key, data), next(next){}
	};
	_Node *root;
	allocator_type		_alloc;
	key_compare			_comp;

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _comp(comp), _alloc(alloc), _Node(NULL){

	}

};

}
#endif // MAP_HPP