#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	test.insert(__NS::make_pair(10, 10));
	std::cout << "=> " << (*test.begin()).first << std::endl;
}