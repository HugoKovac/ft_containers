#include "define_main.hpp"

int main(){
	std::cout << COLOR_RED << "Namespace use : " << __NS_S << COLOR_DEFAULT << std::endl;
	vector_test();
	pair_test();
	map_test();
	stack_test();
	
	return 0;
}
