#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	std::cout << test.size() << " | " << test.empty() << std::endl;

	for (int i = 0; i < 1000000; i++)
		std::cout << test.insert(__NS::make_pair(i, i - 10000)).first->first << std::endl;

	std::cout << test.insert(__NS::make_pair(2, 20)).first->second << std::endl;
	std::cout << test.insert(__NS::make_pair(2, 10000)).first->second << std::endl;
	
	// std::cout << test.insert(test.begin(), __NS::make_pair(10, 1))->second << std::endl;

	std::cout << test.size() << " | " << test.empty() << std::endl;

	__NS::map<int, int>::iterator it = test.begin();
	while (it != test.end()){
		std::cout << it->second << std::endl; 
		it++;
	}
}