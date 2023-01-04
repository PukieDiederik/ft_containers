#include <iostream>
#include "vector.hpp"
//#include <vector>

void vector_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mvectors" << std::endl;
	ft::vector<int> vec(3, 5);
	ft::vector<int> vec2(vec);

	for (ft::vector<int>::iterator i = vec2.begin(); i != vec2.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
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