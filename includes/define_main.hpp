#ifndef DEFINE_MAIN_HPP
#define DEFINE_MAIN_HPP

#include <iostream>

#ifndef STD
# define __NS ft
# define __NS_S "ft"
#else
# define __NS std
# define __NS_S "std"
#endif

#include "vector.hpp"
#include "map.hpp"

#define COLOR_RED "\x1B[31m"
#define COLOR_MAG "\x1B[35m"
#define COLOR_YEL "\x1B[33m"
#define COLOR_DEFAULT "\033[0m"

#define LN std::cout << "line " << COLOR_YEL << __LINE__ << COLOR_DEFAULT << " : "

#define PRINT_SC(v) LN << COLOR_MAG << "size : " << v.size() \
	<< " | capacity " << v.capacity() << COLOR_DEFAULT << std::endl;

void vector_test(void);
void map_test(void);
void pair_test(void);

#endif