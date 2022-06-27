#include "define_main.hpp"

int main(){
	vector_test();
	map_test();

{
	__NS::pair<int,char> foo (10,'z');
	__NS::pair<int,char> bar (90,'a');

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}
{
	std::pair <int,int> foo;
	std::pair <int,int> bar;
	foo = std::make_pair (10,20);
	bar = std::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>	
	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
}
{
	__NS::pair <std::string,double> product1;                     // default constructor
	__NS::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	__NS::pair <std::string,double> product3 (product2);          // copy constructor	
	product1 = __NS::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)	
	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double	
	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
}
  return 0;
}