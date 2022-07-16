#if !defined(STACK_HPP)
#define STACK_HPP

#include "vector.hpp"
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
			Container c;

		public:
		
			explicit stack (const container_type& c = container_type()) : c(c) {}

			bool empty () const { return (c.empty()); }
			size_type size() const { return (c.size()); }
			value_type& top() { return (c.back()); }
			const value_type& top() const { return (c.back()); }
			void push (const value_type& val) { c.push_back(val); }
			void pop() { c.pop_back(); }

	};

	
	template <typename T, typename Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (!(lhs == rhs));  
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c < rhs.c);
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
