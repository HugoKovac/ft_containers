#if !defined(IS_INTEGRAL_HPP)
#define IS_INTEGRAL_HPP

/*is_itegral*/
namespace ft
{
template <bool is_integral, typename T>//struct that contain is_integral_spec
struct integral_sub{
	typedef T type;
	static const bool value = is_integral;
};

//is_integral_spec check if 
template <typename>//default spec (if other spec not find)
struct is_integral_spec : integral_sub<false, bool>{};

template <>//spec for bool
struct is_integral_spec<bool> : public integral_sub<true, bool>{};

template <>//spec for char
struct is_integral_spec<char> : public integral_sub<true, char>{};

template <>//spec for int
struct is_integral_spec<int> : public integral_sub<true, int>{};

template <>//spec for wchar_t
struct is_integral_spec<wchar_t> : public integral_sub<true, wchar_t>{};

template <>//spec for signed char
struct is_integral_spec<signed char> : public integral_sub<true, signed char>{};

template <>//spec for short int
struct is_integral_spec<short int> : public integral_sub<true, short int>{};

template <>//spec for long int
struct is_integral_spec<long int> : public integral_sub<true, long int>{};

template <>//spec for long long int
struct is_integral_spec<long long int> : public integral_sub<true, long long int>{};

template <>//spec for unsigned char
struct is_integral_spec<unsigned char> : public integral_sub<true, unsigned char>{};

template <>//spec for unsigned short int
struct is_integral_spec<unsigned short int> : public integral_sub<true, unsigned short int>{};

template <>//spec for unsigned int
struct is_integral_spec<unsigned int> : public integral_sub<true, unsigned int>{};

template <>//spec for unsigned long int
struct is_integral_spec<unsigned long int> : public integral_sub<true, unsigned long int>{};

template <>//spec for unsigned long long int
struct is_integral_spec<unsigned long long int> : public integral_sub<true, unsigned long long int>{};

//base is_integral function
template <class T>
struct is_integral : public is_integral_spec<T>{};
}
/*End of is itergal*/
#endif // IS_INTEGRAL_HPP
