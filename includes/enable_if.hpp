#if !defined(ENABLE_IF_HPP)
#define ENABLE_IF_HPP

/*enable_if*/
namespace ft
{
template <bool Cond, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> { typedef T type; };
}
/*end of enable_if*/

#endif // ENABLE_IF_HPP
