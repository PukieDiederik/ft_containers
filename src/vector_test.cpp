#include <iostream>
#include <stdexcept>
#include "vector.hpp"
#include <vector>
#include "stl.hpp"

void vector_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mvectors" << std::endl;
	ft::vector<int> vec(3, 5);
	ft::vector<int> vec2(vec);
	ft::vector<int> vec3;
	ft::vector<int> a(vec.begin(), vec.end());
//std::vector<int>::iterator

	for (int i = 0; i < 5; ++i)
	{
		vec3.push_back(i);
	}
	vec3.insert(vec3.end(), 6);
	vec3.insert(vec3.begin() + 1, -3);
	vec3.insert(vec3.begin() + 3, 5, -2);
	vec3.insert(vec3.begin() + 3, vec2.begin(), vec2.end());

	for (ft::vector<int>::iterator i = vec3.begin(); i != vec3.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
	vec3.assign(vec.begin(), vec.end());
	std::cout << "\n---\n" << std::endl;
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