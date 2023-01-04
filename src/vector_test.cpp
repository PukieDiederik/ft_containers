#include <iostream>
#include <stdexcept>
#include "vector.hpp"
//#include <vector>

void vector_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mvectors" << std::endl;
	ft::vector<int> vec(3, 5);
	ft::vector<int> vec2(vec);

	vec2.resize(6, 7);
	for (ft::vector<int>::iterator i = vec2.begin(); i != vec2.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	vec2.resize(2);
	std::cout << "\n";
	for (ft::vector<int>::iterator i = vec2.begin(); i != vec2.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	std::cout << "\n---\n" << std::endl;

	try { vec.at(3) = 6; }
	catch (std::exception& e) {std::cout << e.what() << std::endl; }
	vec.at(2) = 6;
	vec[0] = 4;

	std::cout << "\n---\n" << std::endl;

	// Iterator testing
	for (ft::vector<int>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	std::cout << "\n---\n" << std::endl;
	for (ft::vector<int>::reverse_iterator i = vec.rbegin(); i != vec.rend(); ++i)
	{
		std::cout << *i << std::endl;
	}
}