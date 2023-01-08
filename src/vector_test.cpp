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
	ft::vector<int> v1;
	ft::vector<int> v2;
	ft::vector<int> v3;
	ft::vector<int> v4;

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(4);

	v3.push_back(1);
	v3.push_back(3);
	v3.push_back(3);

	v4 = v2;
	PRINT_CAT(15, "operator==");
	if (!(v4 == v2) || v4 == v3) {
		PRINT_ERR("operator== does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator!=");
	if (v4 != v2 || !(v3 != v1) || !(v1 != v3)) {
		PRINT_ERR("operator!= does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator<");
	if (!(v1 < v2) || !(v2 < v3) || !(v1 < v3) || v3 < v1) {
		PRINT_ERR("operator< does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator>");
	if (!(v2 > v1) || !(v3 > v2) || !(v3 > v1) || v1 > v3) {
		PRINT_ERR("operator> does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator<=");
	if (!(v2 <= v4) || !(v4 <= v2) || !(v1 <= v3) || v3 <= v1) {
		PRINT_ERR("operator<= does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator>=");
	if (!(v2 >= v4) || !(v4 >= v2) || !(v3 >= v1) || v1 >= v3) {
		PRINT_ERR("operator>= does not return correct value");
	}
	else
		std::cout << OK_MSG << std::endl;
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
	{ // at
		PRINT_CAT(15, "at");
		ft::vector<int> v;
		for (int i = 25; i > 0; --i)
		{
			v.push_back(i);
		}
		if (v.at(3) != 22 || v.at(24) != 1 || v.at(12) != 13) {
			PRINT_ERR("Returned incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.at(6) = 99;
		if (v.at(6) != 99) {
			PRINT_ERR("Could not set number");
		}
		else
			std::cout << OK_MSG;
		try { v.at(-1); PRINT_ERR("Did not throw an exception"); }
		catch (std::exception& e) { std::cout << OK_MSG; }
		try { v.at(25); PRINT_ERR("Did not throw an exception"); }
		catch (std::exception& e) { std::cout << OK_MSG << std::endl; }
	}
	{ // operator[]
		PRINT_CAT(15, "operator[]");
		ft::vector<int> v;
		for (int i = 25; i > 0; --i)
		{
			v.push_back(i);
		}
		if (v[3] != 22 || v[24] != 1 || v[12] != 13) {
			PRINT_ERR("Returned incorrect value");
		}
		else
			std::cout << OK_MSG;
		v[6] = 99;
		if (v[6] != 99) {
			PRINT_ERR("Could not set number");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // front
		PRINT_CAT(15, "front");
		ft::vector<int> v;
		v.push_back(5);
		if (v.front() != 5) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.push_back(8);
		if (v.front() != 5) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.erase(v.begin());
		if (v.front() != 8) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // back
		PRINT_CAT(15, "back");
		ft::vector<int> v;
		v.push_back(5);
		if (v.back() != 5) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.push_back(8);
		if (v.back() != 8) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.push_back(-1);
		if (v.back() != -1) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG;
		v.pop_back();
		if (v.back() != 8) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // data
		PRINT_CAT(15, "data");
		ft::vector<int> v;
		for(int i = 0; i < 10; ++i)
		{
			v.push_back(i);
		}
		if (v.data()[3] != 3 || v.data()[6] != 6) {
			PRINT_ERR("Incorrect value");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
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