#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "vector.hpp"
#include <vector>
#include "stl.hpp"

#define PRINT_ERR(MSG) std::cout << "\033[0;31m KO.\033[0m" << std::endl; std::cerr << "\033[0;31m"MSG"\n\033[0m"
#define OK_MSG "\033[0;32mOK. \033[0m"
#define PRINT_CAT(WIDTH,MSG) std::cout << std::left << std::setw(WIDTH) << MSG << ": "

// Checks if all constructors work as expected
static void check_construction()
{
	std::cout << "\033[0;33m> Testing construction\033[0m" << std::endl;
	{ // Default construction
		PRINT_CAT(15,"default");
		ft::vector<int> v;

		if (!v.empty() || v.size() != 0)
		{
			PRINT_ERR("The 'size' of the vector is not 0");
		}
		else if (v.begin() != v.end())
		{
			PRINT_ERR("The begin() and end() iterators are not equal");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // Range-value construction
		PRINT_CAT(15,"range-value");
		std::vector<int> v1_b(5);
		ft::vector<int> v1(5);

		if (v1.empty() || v1.size() != v1_b.size()) {
			PRINT_ERR("Invalid size, expected 5");
		}
		else if (!std::equal(v1.begin(), v1.end(), v1_b.begin())) {
			PRINT_ERR("Invalid values");
		}
		else {
			std::cout << OK_MSG;
		}

		std::vector<int> v2_b(7, 3);
		ft::vector<int> v2(7, 3);
		if (v2.empty() || v2.size() != v2_b.size()) {
			PRINT_ERR("Invalid size, expected 7");
		}
		else if (!std::equal(v2.begin(), v2.end(), v2_b.begin())) {
			PRINT_ERR("Invalid values");
		}
		else {
			std::cout << OK_MSG << std::endl;
		}
	}
	{ // Iterator construction
		PRINT_CAT(15,"iterator");
		std::vector<int> v1_b;
		for (int i = 0; i < 10; ++i)
			v1_b.push_back(i);
		ft::vector<int> v1(v1_b.begin(), v1_b.end());
		if (v1.empty() || v1.size() != v1_b.size()) {
			PRINT_ERR("Invalid size, expected 10");
		}
		else if (!std::equal(v1.begin(), v1.end(), v1_b.begin())) {
			PRINT_ERR("Invalid Values");
		}
		else
			std::cout << OK_MSG;
		v1_b[3] = 99;
		if (v1[3] == v1_b[3]) {
			PRINT_ERR("Modifying original collection alters the other");
		}
		else {
			std::cout << OK_MSG << std::endl;
		}
	}
	{ // Copy constructor
		PRINT_CAT(15,"copy");

		std::vector<int> v_b;
		for (int i = 0; i < 10; ++i)
			v_b.push_back(i);
		ft::vector<int> v1(v_b.begin(), v_b.end());
		ft::vector<int> v2(v1);

		if (v1.size() != v2.size()) {
			PRINT_ERR("Wrong size");
		}
		else if (!std::equal(v1.begin(), v1.end(), v2.begin())){
			PRINT_ERR("Invalid values");
		}
		else
			std::cout << OK_MSG;

		v1[0] = 5;
		if (v1[0] == v2[0]) {
			PRINT_ERR("Modifying the original vector modifies the copy");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // Copy assignment
		PRINT_CAT(13,"copy-assignment");

		std::vector<int> v_b;
		for (int i = 0; i < 10; ++i)
			v_b.push_back(i);
		ft::vector<int> v1(v_b.begin(), v_b.end());
		ft::vector<int> v2 = v1;

		if (v1.size() != v2.size()) {
			PRINT_ERR("Wrong size");
		}
		else if (!std::equal(v1.begin(), v1.end(), v2.begin())){
			PRINT_ERR("Invalid values");
		}
		else
			std::cout << OK_MSG;

		v1[0] = 5;
		if (v1[0] == v2[0]) {
			PRINT_ERR("Modifying the original vector modifies the copy");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

// Checks if comparison operators work as expected
static void check_comparison() {
	std::cout << "\033[0;33m> Testing comparison\033[0m" << std::endl;
	// TODO: < > == != <= >=
}

// Checks if iterators work as expected
static void check_iterator()
{
	std::cout << "\033[0;33m> Testing iterators\033[0m" << std::endl;
	// TODO: begin end rbegin rend
}

// Checks if accessor functions & operators work as expected
static void check_accessor()
{
	std::cout << "\033[0;33m> Testing accessors\033[0m" << std::endl;
	// TODO: at operator[] front back data
}

// Checks if manipulation functions that manipulate the size of the array work as expected
static void check_size_manip()
{
	std::cout << "\033[0;33m> Testing size manipulation\033[0m" << std::endl;
	// TODO: reserve shrink_to_fit resize clear
}

// Checks if regular manipulation functions work
static void check_manip()
{
	std::cout << "\033[0;33m> Testing manipulation\033[0m" << std::endl;
	// TODO: insert erase push_back pop_back
}

// Check functions that didn't fit in another category
static void check_other()
{
	std::cout << "\033[0;33m> Testing other\033[0m" << std::endl;
	// TODO: assign swap std::swap
}

void vector_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mvectors" << std::endl;

	check_construction();
	check_accessor();
	check_iterator();
	check_manip();
	check_size_manip();
	check_other();
	check_comparison();
}