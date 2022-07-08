#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "compare.hpp"
#include "iterator.hpp"

namespace ft{
template < class T, class Alloc = std::allocator<T> >
class vector{
	public :
		typedef Alloc										allocator_type;
		typedef typename allocator_type::value_type			value_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef ft::VectorIter<value_type>					iterator;
		typedef ft::VectorIter<const value_type>			const_iterator;
		typedef RevIter<iterator>							reverse_iterator;
		typedef RevIter<const iterator>						const_reverse_iterator;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

	explicit vector (const allocator_type& alloc = allocator_type()):
		_alloc(alloc),
		_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr)
	{}

	explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()):
		_alloc(alloc),
		_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr)
		{ assign(n, val); }


	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr):
		_alloc(alloc),
		_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr)
	{
		reserve(std::distance(first, last));
		while (first != last)
			*(_end++) = *(first++);
	}

	vector (const vector& x) :_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr){
		insert(_end, x._start, x._end);
	}

	~vector(){
		clear();
		_alloc.deallocate(_start, capacity());
	}

	vector& operator= (const vector& x){
		if (x == *this)
			return *this;
		clear();
		assign(x.begin(), x.end());
		return *this;
	}

	void range_check(size_type const n){
		if (n >= size())
			throw std::out_of_range("ft::at");
	}

	size_type size() const{ return _end - _start; }

	size_type capacity() const{ return _end_capacity - _start; };

	size_type max_size() const{ return _alloc.max_size(); }

	iterator begin(){ return iterator(_start); };

	const_iterator begin() const { return const_iterator(_start); };

	iterator end(){ return iterator(_end); };

	const_iterator end() const { return const_iterator(_end); };


	reverse_iterator rbegin(){ return reverse_iterator(end()); };
	const_reverse_iterator rbegin()const{ return const_reverse_iterator(end()); };

	reverse_iterator rend(){ return reverse_iterator(begin()); };
	const_reverse_iterator rend()const{ return const_reverse_iterator(begin()); };

	void reserve (size_type n){ 
		if (n > max_size())
			throw std::length_error("ft::reserve");
		else if (n > capacity()){
			pointer tmp_start = _start;
			pointer tmp_end = _end;
			size_type old_size = size();

			_start = _alloc.allocate(n);
			_end = _start;
			_end_capacity = _start + n;
			while (tmp_start != tmp_end)
			{
				_alloc.construct(_end, *tmp_start);
				++_end;
				++tmp_start;
			}
			_alloc.deallocate(tmp_end - old_size, old_size);
		}
	}

	bool empty() const{ return (size() == 0 ? true : false); }

	void push_back (const value_type& val){
		if (size() + 1 > capacity())
			reserve((capacity() == 0 ? 1 : capacity() * 2));
		*(_end++) = val;
	}

	reference operator[] (size_type n){ return *(_start + n); }

	const_reference operator[] (size_type n) const{ return *(_start + n); }

	reference at (size_type n){
		range_check(n);
		return *(_start + n);
	}

	const_reference at (size_type n) const{
		range_check(n);
		return *(_start + n);
	}

	reference front(){ return *_start; }

	const_reference front() const{ return *_start; }

	reference back(){ return *(_end - 1); }

	const_reference back() const{ return *(_end - 1); }

	void clear(){
		if (_end != _start)
			while (_end != _start)
				_alloc.destroy(--_end);
	}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
	typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr){
		size_type dist = std::distance(first, last);
		clear();
		if (dist > capacity())
			reserve(dist);
		while (first != last)
			*(_end++) = *(first++);
	}

	void assign (size_type n, const value_type& val){
		clear();
		if (n > capacity())
			reserve(n);
		while (n-- > 0)
			*(_end++) = val;
	}

	void pop_back(){
		if (!empty())
			_alloc.destroy(_end - 1);
		--_end;
	}

	iterator insert (iterator position, const value_type& val){
		difference_type pos_insert = position.operator->() - _start;

		if (capacity() < size() + 1)
			reserve(capacity() * 2);

		reverse_iterator rit = rbegin();
		while (rit != rend() + pos_insert){
			*(rit - 1) = *rit; 
			rit++;
		}
		*(_start + pos_insert) = val;
		++_end;
		return _start + pos_insert;
	}

	void insert (iterator position, size_type n, const value_type& val){
		difference_type pos_insert = position.operator->() - _start;

		if (capacity() < size() + n)
			reserve((size() + n <= capacity() * 2 ? capacity() * 2 : capacity() + n));

		reverse_iterator rit = rbegin();
		while (rit.operator->() != _start + pos_insert){
			*(rit - n) = *rit;
			++rit;
		}
		*(rit - n) = *rit;

		for (size_type i = 0; i < n; i++)
			*(_start + pos_insert + i) = val;

		_end += n;
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr){
		difference_type pos_insert = position.operator->() - _start;
		size_type n = std::distance(first, last);

		if (capacity() < size() + n)
			reserve((size() + n <= capacity() * 2 ? capacity() * 2 : capacity() + n));

		reverse_iterator rit = rbegin();
		while (rit.operator->() != _start + pos_insert && rit.operator->() > _start + pos_insert){
			*(rit - n) = *rit;
			++rit;
		}
		*(rit - n) = *rit;

		for (size_type i = 0; i < n; i++)
			*(_start + pos_insert + i) = *(first++);

		_end += n;
	}

	void resize (size_type n, value_type val = value_type()){
		if (n < size()){
			iterator save(begin() + n);
			while (save != end())
				pop_back();
		}
		else{
			if (n > capacity() * 2)
						this->reserve(n);
			while (n > size()) {
				this->push_back(val);
			}
		}
	}

	iterator erase(iterator position)
	{
		iterator it = position.operator->();
		if (!empty()){
			_alloc.destroy(position.operator->());
			while (it != _end){
				*(it) = *(it + 1);
				it++;
			}
		}
		--_end;
		return position;
	}

	iterator erase (iterator first, iterator last){
		iterator save_first = first;
		if (!empty())
		{
			pointer save_end = _end;
			_end -= std::distance(first, last);
			while (first != last)
				_alloc.destroy((first++).operator->());
			while (last != save_end)
				*(save_first++) = *(last++);
		}
		return save_first - 1;
	}

	void swap (vector& x){
		pointer tmp_start = _start;
		pointer tmp_end = _end;
		pointer tmp_end_capacity = _end_capacity;

		_start = x._start;
		_end = x._end;
		_end_capacity = x._end_capacity;

		x._start = tmp_start;
		x._end = tmp_end;
		x._end_capacity = tmp_end_capacity;
	}

	allocator_type get_allocator() const{
		allocator_type copy;
		return copy;	
	}

	private :
	allocator_type _alloc;
	pointer _start;
	pointer _end;
	pointer _end_capacity;
};

/*operator*/
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return (equal(lhs.begin(), lhs.end(), rhs.begin()) ? true : false);
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ? true : false);
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return !(lhs < rhs);
}
/*end of operator*/

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
	x.swap(y);
}

}

#endif // VECTOR_HPP
