#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP
namespace ft
{
	template <typename T>
	class VectorIter{
	public:
		typedef T											value_type;
		typedef value_type&									reference;
		typedef value_type*									pointer;
		typedef typename std::ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag		iterator_category;



		VectorIter() : _ptr(nullptr){}
		VectorIter(pointer ptr) : _ptr(ptr){}
		VectorIter(VectorIter const &src) { *this = src; }
		virtual ~VectorIter(){}

		VectorIter &operator=(VectorIter const &src) { _ptr = src.operator->(); return (*this); };

		reference operator*(){ return *_ptr; }
		reference operator*() const{ return *_ptr; }

		VectorIter operator +(difference_type b) { return (VectorIter(_ptr + b)); };
		VectorIter operator +(difference_type b) const{ return (VectorIter(_ptr + b)); };
		VectorIter operator -(difference_type b) { return (VectorIter(_ptr - b)); };
		VectorIter operator -(difference_type b) const{ return (VectorIter(_ptr - b)); };

		bool operator ==(VectorIter const &rhs) const{ return _ptr == rhs._ptr; }
		bool operator !=(VectorIter const &rhs) const{ return _ptr != rhs._ptr; }

		bool operator <(VectorIter const &rhs) const{ return _ptr < rhs._ptr; }
		bool operator <=(VectorIter const &rhs) const{ return _ptr <= rhs._ptr; }

		bool operator >(VectorIter const &rhs) const{ return _ptr > rhs._ptr; }
		bool operator >=(VectorIter const &rhs) const{ return _ptr >= rhs._ptr; }

		VectorIter operator ++(){ ++_ptr; return *this; }
		VectorIter operator ++(int){ VectorIter cpy = *this; ++_ptr; return cpy; }

		VectorIter operator --(){ --_ptr; return *this; }
		VectorIter operator --(int){ VectorIter cpy = *this; --_ptr; return cpy; }

		VectorIter &operator +=(difference_type rhs){ _ptr += rhs; return *this; }
		VectorIter &operator -=(difference_type rhs){ _ptr -= rhs; return *this; }

		reference operator[](difference_type const n) { return *(_ptr + n); }
		reference operator[](difference_type const n) const { return *(_ptr + n); }
		pointer operator->() { return &(this->operator*()); }
		pointer operator->() const { return &(this->operator*()); }

	private :
		pointer _ptr;
	};

	template <class Iterator>
	VectorIter<Iterator> operator+ ( typename VectorIter<Iterator>::difference_type n, const VectorIter<Iterator>& rev_it){
		return VectorIter<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename VectorIter<Iterator>::difference_type operator- (const VectorIter<Iterator>& lhs, const VectorIter<Iterator>& rhs){
		return lhs.operator->() - rhs.operator->();
	}
	/*End of VectorRevIter operators*/

	template< class Iterator >
	struct iterator_traits{
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>{
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*>{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class Iterator>
	class VectorRevIter{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

		VectorRevIter() : _it(){}

		explicit VectorRevIter (iterator_type it) : _it(it){}
	
		template <class Iter>
		VectorRevIter (const VectorRevIter<Iter>& rev_it){ _it = rev_it.base(); }

		iterator_type base() const{ return _it; }

		reference operator*() const{ iterator_type cpy = _it; return *(--cpy); }
		reference operator[] (difference_type n) const{ return base()[-n - 1]; }
		pointer operator->() const{ return &(operator*()); }

		VectorRevIter operator+ (difference_type n) const { return VectorRevIter(_it - n); }
		VectorRevIter operator- (difference_type n) const { return VectorRevIter(_it + n); }

		VectorRevIter & operator-= (difference_type n){ _it += n; return *this; }
		VectorRevIter & operator+= (difference_type n){ _it -= n; return *this; }

		VectorRevIter& operator++(){ --_it; return *this; }
		VectorRevIter  operator++(int){ VectorRevIter temp = *this; ++(*this); return temp; }
		VectorRevIter& operator--(){ ++_it; return *this; }
		VectorRevIter  operator--(int){ VectorRevIter temp = *this; --(*this); return temp; }
	private:
		iterator_type _it;
	};

	/*VectorRevIter operators*/
	template <class Iterator>
	bool operator== (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<  (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>  (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>= (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	VectorRevIter<Iterator> operator+ ( typename VectorRevIter<Iterator>::difference_type n, const VectorRevIter<Iterator>& rev_it){
		return VectorRevIter<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename VectorRevIter<Iterator>::difference_type operator- (const VectorRevIter<Iterator>& lhs, const VectorRevIter<Iterator>& rhs){
		return rhs.operator->() - lhs.operator->();
	}
	/*End of VectorRevIter operators*/

	template <typename N, typename T>
	class MapIter{
	public:
		typedef T 								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef N								node_type;
		typedef N*								node_pointer;
		typedef N&								node_reference;
		typedef typename std::ptrdiff_t			difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

		MapIter() : _Nptr(nullptr){}
		MapIter(node_pointer Nptr, bool end = false) : _Nptr(Nptr), _end(end){}
		MapIter(MapIter const &src) { *this = src; }
		virtual ~MapIter(){}

		reference operator*(){ return *_Nptr->value; }
		reference operator*() const{ return *_Nptr->value; }

		
	private:
		node_pointer	_Nptr;
		node_pointer	_root;
		bool			_end;
	};
}

#endif // ITERATOR_HPP