#include "define_main.hpp"
#include <deque>

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
	{
		__NS::stack<int, std::deque<int>> test2;

		std::cout << test2.empty() << std::endl;
		std::cout << test2.size() << std::endl;

		for (int i = 0; i < 30; i++)
			test2.push(i);

		std::cout << test2.empty() << std::endl;
		std::cout << test2.size() << std::endl;
		std::cout << test2.top() << std::endl;
		test2.pop();
		std::cout << test2.top() << std::endl;
	}
}