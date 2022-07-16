#if !defined(STACK_HPP)
#define STACK_HPP

#include "vector.hpp"
#include <iostream>//!remove
namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {
		
		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;
		
			template <typename _T, typename _Container>
			friend bool	ft::operator==(stack<_T, _Container> const &lhs,
			stack<_T, _Container> const &rhs);

			template <typename _T, typename _Container>
			friend bool	ft::operator<(stack<_T, _Container> const &lhs,
			stack<_T, _Container> const &rhs);
			
		protected:
			Container ctnr;

		public:
		
			explicit stack (const container_type& ctnr = container_type()) : ctnr(ctnr) {}

			bool empty () const { return (ctnr.empty()); }
			size_type size() const { return (ctnr.size()); }
			value_type& top() { return (ctnr.back()); }
			const value_type& top() const { return (ctnr.back()); }
			void push (const value_type& val) { ctnr.push_back(val); }
			void pop() { ctnr.pop_back(); }

	};

	
	template <typename T, typename Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.ctnr == rhs.ctnr);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (!(lhs == rhs));  
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.ctnr < rhs.ctnr);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs < rhs || lhs == rhs);
	}
	
	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs > rhs || lhs == rhs);
	}
}

#endif // STACK_HPP
