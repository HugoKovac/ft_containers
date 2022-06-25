#include "define_main.hpp"

template <class vec>
void printDataVector(vec begin, vec end){
	LN;
	std::cout << "{";
	for (; begin != end; begin++)
	{
		std::cout << *begin;
		if (begin + 1 != end)
			std::cout << ", ";
	}
	std::cout << "}" << std::endl;
}

void vector_test(void){
	std::cout << COLOR_RED << "Namespace use : " << __NS_S << COLOR_DEFAULT << std::endl;
	__NS::vector<int> v1(5, -1);

	PRINT_SC(v1);
//* iterator
	std::cout << "test iterator : / begin() / end()" << std::endl;

	printDataVector(v1.begin(), v1.end());
//* reverse_iterator
	{
		std::cout << "{";
		__NS::vector<int>::reverse_iterator rit = v1.rbegin();
		for (; rit != v1.rend(); rit++)
		{
			std::cout << *rit;
			if (rit + 1 != v1.rend())
				std::cout << ", ";
		}
		std::cout << "}" << std::endl;
	}
//*clear
	v1.clear();
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
//*push_swap
	for (int i = 0; i < 6 ; i++){
		v1.push_back(i);
		PRINT_SC(v1);
		printDataVector(v1.begin(), v1.end());
	}
//* operator[]
	for (__NS::vector<int>::size_type i = 0; i < v1.size(); i++)
		std::cout << v1[i] << std::endl;
//* at
	for (__NS::vector<int>::size_type i = 0; i < v1.size(); i++)
		std::cout << v1.at(i) << std::endl;
//* front back
	std::cout << v1.front() << " " << v1.back() << std::endl;
//* max_size
	std::cout << v1.max_size() << std::endl;
//* empty
	std::cout << v1.empty() << std::endl;
//* reserve
	v1.reserve(10);
	PRINT_SC(v1);
//*Iter operator
{
	__NS::vector<int>::iterator it = v1.begin();
	__NS::vector<int>::iterator it2 = v1.begin() + 2;

	LN << *(it) << std::endl;//operator*
	LN << *(it + 2) << std::endl;//operator+
	LN << *(it += 2) << std::endl;//operator+=
	LN << it[2] << std::endl;//operator[]
	LN << *(it - 2) << std::endl;//operator-
	LN << *(it -= 2) << std::endl;//operator-=
	LN << *(it.operator->()) << std::endl;//operator->
	LN << (it2 - it) << std::endl;//operator- extern
	LN << ((1 + it) - it) << std::endl;//operator+ extern
//*RevIter relation operator
	std::cout << std::boolalpha;
	LN << (it < it2) << std::endl;
	LN << (it > it2) << std::endl;
	LN << (it + 2 == it2) << std::endl;
	LN << (it + 2 != it2) << std::endl;
	LN << (it >= it2) << std::endl;
	LN << (it <= it2) << std::endl;
	std::cout << std::noboolalpha << std::endl;
}
//*RevIter operator
{
	__NS::vector<int>::reverse_iterator rit = v1.rbegin();
	__NS::vector<int>::reverse_iterator rit2 = v1.rbegin() + 2;

	LN << *(rit) << std::endl;//operator*
	LN << *(rit + 2) << std::endl;//operator+
	LN << *(rit += 2) << std::endl;//operator+=
	LN << rit[2] << std::endl;//operator[]
	LN << *(rit - 2) << std::endl;//operator-
	LN << *(rit -= 2) << std::endl;//operator-=
	LN << *(rit.operator->()) << std::endl;//operator->
	LN << (rit2 - rit) << std::endl;//operator- extern
	LN << ((1 + rit) - rit) << std::endl;//operator+ extern
//*RevIter relation operator
	std::cout << std::boolalpha;
	LN << (rit < rit2) << std::endl;
	LN << (rit > rit2) << std::endl;
	LN << (rit + 2 == rit2) << std::endl;
	LN << (rit + 2 != rit2) << std::endl;
	LN << (rit >= rit2) << std::endl;
	LN << (rit <= rit2) << std::endl;
	std::cout << std::noboolalpha << std::endl;
}
//*opeartor[]
	LN << v1[2] << std::endl;
//* assign
{
	v1.assign(5, 3);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());

	__NS::vector<int> tmp(5, -1);
	v1.assign(tmp.begin(), tmp.end());
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
}
//*pop_back
	v1.pop_back();
	PRINT_SC(v1);
	LN << (v1.end() - v1.begin()) << std::endl;
	printDataVector(v1.begin(), v1.end());
//*erase
	for (int i = 0; i < 20 ; i++)
		v1.push_back(i);
	v1.erase(v1.begin() + 2);
	v1.erase(v1.begin() + 2, v1.begin() + 8);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
//*swap
{
	__NS::vector<int> tmp(5, -1);
	v1.swap(tmp);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
	v1.swap(tmp);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
}
// //*swap extern
	__NS::vector<int> tmp(5, -1);
	__NS::swap(v1, tmp);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
	__NS::swap(v1, tmp);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
//*insert
	std::cout << *(v1.insert(v1.begin(), 0)) << std::endl;
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());

	v1.insert(v1.begin(), 2, 1);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());

{
	__NS::vector<int> tmp(5, 10);

	v1.insert(v1.begin() + 2, tmp.begin(), tmp.end());
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
}
//*resize
	v1.resize(20);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
	v1.resize(40, -2);
	PRINT_SC(v1);
	printDataVector(v1.begin(), v1.end());
//*constructors
{
	__NS::vector<int> tmp;
	PRINT_SC(tmp);
	printDataVector(tmp.begin(), tmp.end());
}
{
	__NS::vector<int> tmp(10, 2);
	PRINT_SC(tmp);
	printDataVector(tmp.begin(), tmp.end());
}
{
	__NS::vector<int> tmp(v1.begin() + 2, v1.end());
	PRINT_SC(tmp);
	printDataVector(tmp.begin(), tmp.end());
}
{
	__NS::vector<int> tmp(v1);
	PRINT_SC(tmp);
	printDataVector(tmp.begin(), tmp.end());
}
}