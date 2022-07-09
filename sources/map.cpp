#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	std::cout << test.size() << " | " << test.empty() << std::endl;

	for (int i = 0; i < 100; i++)
		std::cout << test.insert(__NS::make_pair(i, i)).first->first << std::endl;

	std::cout << test.insert(__NS::make_pair(2, 20)).first->second << std::endl;
	std::cout << test.insert(__NS::make_pair(2, 10000)).first->second << std::endl;

	std::cout << (test[3] = 13) << std::endl;
	std::cout << (test[3] = 13) << std::endl;
	
	// std::cout << test.insert(test.begin(), __NS::make_pair(10, 1))->second << std::endl;

	std::cout << test.size() << " | " << test.empty() << std::endl;


	__NS::map<int, int>::iterator save = test.find(10);
	__NS::map<int, int>::iterator save2 = test.find(-10);
	if (save != test.end())
		std::cout << save->first << std::endl;
	if (save2 != test.end())
		std::cout << save2->first << std::endl;

	__NS::map<int, int>::iterator it = test.begin();
	while (it != test.end()){
		std::cout << it->second << std::endl; 
		it++;
	}

	__NS::map<int, int>::reverse_iterator rit = test.rbegin();
	while (rit != test.rend()){
		std::cout << rit->second << std::endl; 
		rit++;
	}
}