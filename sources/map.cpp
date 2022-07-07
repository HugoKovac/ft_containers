#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	test.insert(__NS::make_pair(10, 10));
	test.insert(__NS::make_pair(2, 2));
	test.insert(__NS::make_pair(1, 10));
	test.insert(__NS::make_pair(3, 2));
	test.insert(__NS::make_pair(5, 10));
	test.insert(__NS::make_pair(6, 2));
	test.insert(__NS::make_pair(9, 10));
	test.insert(__NS::make_pair(7, 2));
	test.insert(__NS::make_pair(0, 10));
	test.insert(__NS::make_pair(-12, 2));

	__NS::map<int, int>::iterator it = test.begin();
	while (it != test.end()){
		std::cout << it->first << std::endl; 
		it++;
	}
	// std::cout << "end => " << (*test.end()).first << std::endl;
}