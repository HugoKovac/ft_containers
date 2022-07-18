#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP
namespace ft
{
	template <typename T>
	class VectorIter
	{
	public:
		typedef T value_type;
		typedef value_type &reference;
		typedef value_type *pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;

		VectorIter() : _ptr(NULL) {}
		VectorIter(pointer ptr) : _ptr(ptr) {}
		VectorIter(VectorIter const &src) { *this = src; }
		virtual ~VectorIter() {}

		operator VectorIter<const T>()const{ return (VectorIter<const T>(this->_ptr)); }

		VectorIter &operator=(VectorIter const &src)
		{
			_ptr = src.operator->();
			return (*this);
		};

		reference operator*() { return *_ptr; }
		reference operator*() const { return *_ptr; }

		VectorIter operator+(difference_type b) { return (VectorIter(_ptr + b)); };
		VectorIter operator+(difference_type b) const { return (VectorIter(_ptr + b)); };
		VectorIter operator-(difference_type b) { return (VectorIter(_ptr - b)); };
		VectorIter operator-(difference_type b) const { return (VectorIter(_ptr - b)); };

		bool operator==(VectorIter const &rhs) const { return _ptr == rhs._ptr; }
		bool operator!=(VectorIter const &rhs) const { return _ptr != rhs._ptr; }

		bool operator<(VectorIter const &rhs) const { return _ptr < rhs._ptr; }
		bool operator<=(VectorIter const &rhs) const { return _ptr <= rhs._ptr; }

		bool operator>(VectorIter const &rhs) const { return _ptr > rhs._ptr; }
		bool operator>=(VectorIter const &rhs) const { return _ptr >= rhs._ptr; }

		VectorIter operator++()
		{
			++_ptr;
			return *this;
		}
		VectorIter operator++(int)
		{
			VectorIter cpy = *this;
			++_ptr;
			return cpy;
		}

		VectorIter operator--()
		{
			--_ptr;
			return *this;
		}
		VectorIter operator--(int)
		{
			VectorIter cpy = *this;
			--_ptr;
			return cpy;
		}

		VectorIter &operator+=(difference_type rhs)
		{
			_ptr += rhs;
			return *this;
		}
		VectorIter &operator-=(difference_type rhs)
		{
			_ptr -= rhs;
			return *this;
		}

		pointer base() const { return _ptr; }

		reference operator[](difference_type const n) { return *(_ptr + n); }
		reference operator[](difference_type const n) const { return *(_ptr + n); }
		pointer operator->() { return &(this->operator*()); }
		pointer operator->() const { return &(this->operator*()); }

	private:
		pointer _ptr;
	};

	template <typename T>
	bool operator==(const VectorIter<const T> &lhs, const VectorIter<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const VectorIter<const T> &lhs, const VectorIter<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator<(const VectorIter <const T>&lhs, const VectorIter<T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool operator<=(const VectorIter<const T> &lhs, const VectorIter<T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>(const VectorIter<const T> &lhs, const VectorIter<T> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator>=(const VectorIter<const T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T>
	bool operator==(const VectorIter<T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const VectorIter<T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator<(const VectorIter <T>&lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool operator<=(const VectorIter<T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>(const VectorIter<T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator>=(const VectorIter<T> &lhs, const VectorIter<const T> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	/*End of RevIter operators*/

	template <class Iterator>
	struct iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class RevIter
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

		RevIter() : _it() {}

		explicit RevIter(iterator_type it) : _it(it) {}

		template <class Iter>
		RevIter(const RevIter<Iter> &rev_it) { _it = rev_it.base(); }

		iterator_type base() const { return _it; }

		reference operator*() const
		{
			iterator_type cpy = _it;
			return *(--cpy);
		}
		reference operator[](difference_type n) const { return base()[-n - 1]; }
		pointer operator->() const { return &(operator*()); }

		RevIter operator+(difference_type n) const { return RevIter(_it - n); }
		RevIter operator-(difference_type n) const { return RevIter(_it + n); }

		RevIter &operator-=(difference_type n)
		{
			_it += n;
			return *this;
		}
		RevIter &operator+=(difference_type n)
		{
			_it -= n;
			return *this;
		}

		RevIter &operator++()
		{
			--_it;
			return *this;
		}
		RevIter operator++(int)
		{
			RevIter temp = *this;
			++(*this);
			return temp;
		}
		RevIter &operator--()
		{
			++_it;
			return *this;
		}
		RevIter operator--(int)
		{
			RevIter temp = *this;
			--(*this);
			return temp;
		}

	private:
		iterator_type _it;
	};

	/*RevIter operators*/
	template <class Iterator>
	RevIter<Iterator> operator+(typename RevIter<Iterator>::difference_type n, const RevIter<Iterator> &rev_it)
	{
		return RevIter<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename RevIter<Iterator>::difference_type operator-(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return rhs.operator->() - lhs.operator->();
	}

	template <class Iterator>
	VectorIter<Iterator> operator+(typename VectorIter<Iterator>::difference_type n, const VectorIter<Iterator> &rev_it)
	{
		return VectorIter<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename VectorIter<Iterator>::difference_type operator-(const VectorIter<Iterator> &lhs, const VectorIter<Iterator> &rhs)
	{
		return lhs.operator->() - rhs.operator->();
	}

	template <class Iterator>
	bool operator==(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	// template <class Iterator>
	// RevIter<Iterator> operator+(typename RevIter<Iterator>::difference_type n, const RevIter<Iterator> &rev_it)
	// {
	// 	return RevIter<Iterator>(rev_it + n);
	// }

	// template <class Iterator>
	// typename RevIter<Iterator>::difference_type operator-(const RevIter<Iterator> &lhs, const RevIter<Iterator> &rhs)
	// {
	// 	return rhs.operator->() - lhs.operator->();
	// }
	/*End of RevIter operators*/

	template <typename N, typename T>
	class MapIter
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef N node_type;
		typedef N *node_pointer;
		typedef N &node_reference;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		MapIter(node_pointer root) : _Nptr(NULL), _root(root){}
		MapIter(node_pointer Nptr, node_pointer root) : _Nptr(Nptr), _root(root){}
		MapIter(MapIter const &src) { *this = src; }
		virtual ~MapIter() {}

		MapIter &operator=(MapIter const &src){
			_Nptr = src._Nptr;
			_root = src._root;
			_end = src._end;
			return *this;
		}

	private:
		node_pointer _min(node_pointer n)
		{
			node_pointer tmp;
			tmp = n;

			while (tmp && tmp->left)
				tmp = tmp->left;

			return tmp;
		}

		node_pointer _max(node_pointer n)
		{
			node_pointer tmp;
			tmp = n;

			while (tmp && tmp->right)
				tmp = tmp->right;

			return tmp;
		}

		node_pointer _next(node_pointer n)
		{
			if (n == _max(_root))
				return NULL;
			if (n->right)
				return (_min(n->right));
			node_pointer parent = n->parent;
			while (parent && n == parent->right)
			{
				n = parent;
				parent = parent->parent;
			}
			// std::cout << "address of value : " << reinterpret_cast<void*>(parent) << std::endl;
			// std::cout << "value of address : " << parent->value->first << std::endl;
			return (parent);
		}

		node_pointer _prev(node_pointer n)
		{
			if (n->left)
				return (_max(n->left));
			node_pointer parent = n->parent;
			while (parent && n == parent->left)
			{
				n = parent;
				parent = parent->parent;
			}
			return (parent);
		}

	public:
		friend bool operator==(const MapIter &lhs, const MapIter &rhs) { return lhs._Nptr == rhs._Nptr; };
		friend bool operator!=(const MapIter &lhs, const MapIter &rhs) { return lhs._Nptr != rhs._Nptr; };

		reference operator*() { return *_Nptr->value; }
		reference operator*() const { return *_Nptr->value; }

		MapIter operator++()
		{
			_Nptr = _next(_Nptr);
			return *this;
		}
		MapIter operator++(int)
		{
			MapIter cpy(_Nptr);
			_Nptr = _next(_Nptr);
			return cpy;
		}

		MapIter operator--()
		{
			if (!_Nptr)
				_Nptr = _max(_root);
			else
				_Nptr = _prev(_Nptr);
			return *this;
		}
		MapIter operator--(int)
		{
			MapIter cpy(_Nptr);
			if (!_Nptr)
				_Nptr = _max(_root);
			else
				_Nptr = _prev(_Nptr);
			return cpy;
		}

		pointer operator->() const { return &(operator*()); }

	private:
		node_pointer	_Nptr;
		node_pointer	_root;
		bool			_end;
	};
}

#endif // ITERATOR_HPP