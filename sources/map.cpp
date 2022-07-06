#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	test.insert(__NS::make_pair(10, 10));
	test.insert(__NS::make_pair(2, 2));
	std::cout << "begin => " << (*test.begin()).first << std::endl;
	// std::cout << "end => " << (*test.end()).first << std::endl;
}