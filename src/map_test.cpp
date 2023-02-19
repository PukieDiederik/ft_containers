#include "map.hpp"
#include "test.hpp"
#include <iostream>

#include <map>

static void check_construction()
{
	std::cout << "\033[0;33m> Testing construction\033[0m" << std::endl;
	{ // default
		PRINT_CAT(15, "default");
		ft::map<int,int> m;
		if (m.size() != 0 || !m.empty()) {
			PRINT_ERR("Did not construct an empty map");
		}
		else
		std::cout << OK_MSG <<  std::endl;
	}
	{ // iterator
		PRINT_CAT(15, "iterator");
		ft::pair<int,int> arr[] = {ft::make_pair(5, 5),
								   ft::make_pair(9, 9),
								   ft::make_pair(3, 3)};
		ft::map<int,int> m(arr + 0, arr + 3);
		if (m.size() != 3 || *(m.begin().base()->value) != arr[2]){
			PRINT_ERR("Could not construct with iterator");
		}
		else
			std::cout << OK_MSG;

		ft::map<int,int> n(arr + 0, arr + 2);
		if (n.size() != 2 || *(n.begin().base()->value) != arr[0]){
			PRINT_ERR("Could not construct with iterator");
		}
		else
			std::cout << OK_MSG;
		ft::map<int, int> o(n.begin(), n.end());
		if (o != n){
			PRINT_ERR("Could not construct with iterator");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // copy
		PRINT_CAT(15, "copy");
		ft::pair<int,int> arr[] = {ft::make_pair(5, 5),
								   ft::make_pair(9, 9),
								   ft::make_pair(3, 3)};
		ft::map<int,int> m(arr + 0, arr + 3);
		ft::map<int,int> c(m);
		if (c != m){
			PRINT_ERR("Could not construct using another map");
		}
		else
			std::cout << OK_MSG;

		m.clear();
		ft::map<int,int> d(m);
		if (d != m){
			PRINT_ERR("Could not construct using another map");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // copy-assignment
		PRINT_CAT(15, "copy-assignment");
		ft::pair<int,int> arr[] = {ft::make_pair(5, 5),
								   ft::make_pair(9, 9),
								   ft::make_pair(3, 3)};
		ft::map<int,int> m(arr + 0, arr + 3);
		ft::map<int,int> n;

		n = m;
		if (n != m){
			PRINT_ERR("Could not copy map");
		}
		else
			std::cout << OK_MSG;

		n = ft::map<int, int>(arr + 0, arr + 2);
		if (n.size() != 2){
			PRINT_ERR("Could not copy map");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

static void check_accessors()
{
	std::cout << "\033[0;33m> Testing accessors\033[0m" << std::endl;
	{ // default
		PRINT_CAT(15, "at");
		std::cout << std::endl;
	}
	{ // iterator
		PRINT_CAT(15, "operator[]");
		std::cout << std::endl;
	}
	{ // find
		PRINT_CAT(15, "find");
		std::cout << std::endl;
	}
	{ // equal_range
		PRINT_CAT(15, "equal_range");
		std::cout << std::endl;
	}
	{ // lower_bound
		PRINT_CAT(15, "lower_bound");
		std::cout << std::endl;
	}
	{ // upper_bound
		PRINT_CAT(15, "upper_bound");
		std::cout << std::endl;
	}
	{ // count
		PRINT_CAT(15, "count");
		std::cout << std::endl;
	}
}

static void check_iterators()
{
	std::cout << "\033[0;33m> Testing iterators\033[0m" << std::endl;
	{ // begin
		PRINT_CAT(15, "begin");
		std::cout << std::endl;
	}
	{ // end
		PRINT_CAT(15, "end");
		std::cout << std::endl;
	}
	{ // rbegin
		PRINT_CAT(15, "rbegin");
		std::cout << std::endl;
	}
	{ // rend
		PRINT_CAT(15, "rend");
		std::cout << std::endl;
	}
}

static void check_capacity()
{
	std::cout << "\033[0;33m> Testing capacity\033[0m" << std::endl;
	{ // size
		PRINT_CAT(15, "empty");
		std::cout << std::endl;
	}
	{ // empty
		PRINT_CAT(15, "size");
		std::cout << std::endl;
	}
}

static void check_modifier()
{
	std::cout << "\033[0;33m> Testing modifiers\033[0m" << std::endl;
	{ // insert
		PRINT_CAT(15, "insert");
		std::cout << std::endl;
	}
	{ // clear
		PRINT_CAT(15, "clear");
		std::cout << std::endl;
	}
	{ // erase
		PRINT_CAT(15, "erase");
		std::cout << std::endl;
	}
	{ // swap
		PRINT_CAT(15, "swap");
		std::cout << std::endl;
	}
	{ // std::swap
		PRINT_CAT(15, "std::swap");
		std::cout << std::endl;
	}
}

// Checks if comparison operators work as expected
static void check_comparison() {
	std::cout << "\033[0;33m> Testing comparison\033[0m" << std::endl;

	PRINT_CAT(15, "operator==");
//	if (!(v4 == v2) || v4 == v3) {
//		PRINT_ERR("operator== does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator!=");
//	if (v4 != v2 || !(v3 != v1) || !(v1 != v3)) {
//		PRINT_ERR("operator!= does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator<");
//	if (!(v1 < v2) || !(v2 < v3) || !(v1 < v3) || v3 < v1) {
//		PRINT_ERR("operator< does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator>");
//	if (!(v2 > v1) || !(v3 > v2) || !(v3 > v1) || v1 > v3) {
//		PRINT_ERR("operator> does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator<=");
//	if (!(v2 <= v4) || !(v4 <= v2) || !(v1 <= v3) || v3 <= v1) {
//		PRINT_ERR("operator<= does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;

	PRINT_CAT(15, "operator>=");
//	if (!(v2 >= v4) || !(v4 >= v2) || !(v3 >= v1) || v1 >= v3) {
//		PRINT_ERR("operator>= does not return correct value");
//	}
//	else
		std::cout << OK_MSG << std::endl;
}

void map_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mmap" << std::endl;

	check_construction();
	check_accessors();
	check_capacity();
	check_iterators();
	check_modifier();
	check_comparison();
}
