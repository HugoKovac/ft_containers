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

	std::cout << test.count(10) << std::endl;
	std::cout << test.count(-10) << std::endl;

	{
		__NS::map<int, int> tmp;

		tmp.insert(test.begin(), test.end());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp(test.begin(), test.end());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp(test);//! double free in map(map const &src)

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}

		tmp.clear();
		
		tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl;
			tmp_it++;
		}
	}

	// {//*swap don't work yet
	// 	__NS::map<int, int> tmp;

	// 	for (int i = 100; i < 300; i++)
	// 		tmp.insert(__NS::make_pair(i, i));

	// 	tmp.swap(test);

	// 	__NS::map<int, int>::iterator tmp_it = tmp.begin();
	// 	while (tmp_it != tmp.end()){
	// 		std::cout << tmp_it->second << std::endl; 
	// 		tmp_it++;
	// 	}

	// 	tmp.swap(test);

	// 	tmp_it = tmp.begin();
	// 	while (tmp_it != tmp.end()){
	// 		std::cout << tmp_it->second << std::endl; 
	// 		tmp_it++;
	// 	}
	// }

	{
		__NS::map<int, int> tmp;

		tmp = test;

		for (__NS::map<int, int>::size_type i = tmp.size(); i > 0; i--)
			tmp.erase(tmp.begin());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		tmp.erase(10);
		tmp.erase(21);

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}

		// tmp.erase(tmp.begin(), tmp.end());//! erase range seg. fault some times

		tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			std::cout << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}
}