#include "define_main.hpp"

void stack_test(void){
	__NS::stack<int> test;

	std::cout << test.empty() << std::endl;
	std::cout << test.size() << std::endl;

	for (int i = 0; i < 30; i++)
		test.push(i);

	std::cout << test.empty() << std::endl;
	std::cout << test.size() << std::endl;
	std::cout << test.top() << std::endl;
	test.pop();
	std::cout << test.top() << std::endl;
}