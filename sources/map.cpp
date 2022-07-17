#include "define_main.hpp"

void map_test(void){
	__NS::map<int, int> test;

	LN << test.size() << " | " << test.empty() << std::endl;

	for (int i = 0; i < 100; i++)
		LN << test.insert(__NS::make_pair(i, i + 10)).first->second << std::endl;

	LN << test.insert(__NS::make_pair(2, 20)).first->second << std::endl;
	LN << test.insert(__NS::make_pair(2, 10000)).first->second << std::endl;

	LN << (test[3] = 13) << std::endl;
	LN << (test[3] = 13) << std::endl; 
	
	LN << test.size() << " | " << test.empty() << std::endl;


	__NS::map<int, int>::iterator save = test.find(10000);
	__NS::map<int, int>::iterator save2 = test.find(-10);
	if (save != test.end())
		LN << save->first << std::endl;
	if (save2 != test.end())
		LN << save2->first << std::endl;

	__NS::map<int, int>::iterator it = test.begin();
	while (it != test.end()){
		LN << it->second << std::endl; 
		it++;
	}

	__NS::map<int, int>::reverse_iterator rit = test.rbegin();
	while (rit != test.rend()){
		LN << rit->second << std::endl; 
		rit++;
	}

	LN << test.count(10) << std::endl;
	LN << test.count(-10) << std::endl;

	{
		__NS::map<int, int> tmp;

		tmp.insert(test.begin(), test.end());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp(test.begin(), test.end());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp(test);

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}

		tmp.clear();
		
		__NS::map<int, int>::iterator tmp_it2 = tmp.begin();
		while (tmp_it2 != tmp.end()){
			LN << tmp_it2->second << std::endl;
			tmp_it2++;
		}
	}

	{
		__NS::map<int, int> tmp;

		for (int i = 100; i < 300; i++)
			tmp.insert(__NS::make_pair(i, i));

		tmp.swap(test);

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}

		tmp.swap(test);

		__NS::map<int, int>::iterator tmp_it2 = tmp.begin();
		while (tmp_it2 != tmp.end()){
			LN << tmp_it2->second << std::endl; 
			tmp_it2++;
		}
	}

	{
		__NS::map<int, int> tmp;

		tmp = test;

		for (__NS::map<int, int>::size_type i = tmp.size(); i > 0; i--)
			tmp.erase(tmp.begin());

		__NS::map<int, int>::iterator tmp_it = tmp.begin();
		while (tmp_it != tmp.end()){
			LN << tmp_it->second << std::endl; 
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
			LN << tmp_it->second << std::endl; 
			tmp_it++;
		}

		tmp.erase(tmp.begin(), tmp.end());

		__NS::map<int, int>::iterator tmp_it2 = tmp.begin();
		while (tmp_it2 != tmp.end()){
			LN << tmp_it2->second << std::endl; 
			tmp_it2++;
		}
	}

	LN << test.lower_bound(10)->first << std::endl;
	LN << test.lower_bound(20)->first << std::endl;
	LN << test.lower_bound(43)->first << std::endl;
	LN << test.lower_bound(1)->first << std::endl;
	LN << (test.lower_bound(10000) == test.end()) << std::endl;
	LN << (test.lower_bound(-10000) == test.end()) << std::endl;

	LN << test.upper_bound(10)->first << std::endl;
	LN << test.upper_bound(20)->first << std::endl;
	LN << test.upper_bound(43)->first << std::endl;
	LN << test.upper_bound(1)->first << std::endl;
	LN << (test.upper_bound(10000) == test.end()) << std::endl;
	LN << (test.upper_bound(-10000) == test.end()) << std::endl;

	LN << test.equal_range(10).first->first << std::endl;
	LN << test.equal_range(20).first->second << std::endl;
	LN << test.equal_range(43).second->first << std::endl;
	LN << test.equal_range(1).second->second << std::endl;

	{
		__NS::map<int, int> one;
		__NS::map<int, int> two;

		for (int i = 0; i < 100; i++)
			one.insert(__NS::make_pair(i, i - 100));

		for (int i = 100; i < 200; i++)
			two.insert(__NS::make_pair(i, i - 100));

		std::cout << std::boolalpha;
		LN << (one < two) << std::endl;
		LN << (one > two) << std::endl;
		LN << (one == two) << std::endl;
		LN << (one != two) << std::endl;
		LN << (one >= two) << std::endl;
		LN << (one <= two) << std::endl;
		std::cout << std::noboolalpha << std::endl;
	}

}