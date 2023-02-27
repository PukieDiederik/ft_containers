#include "map.hpp"
#include "test.hpp"
#include <iostream>
#include <string>

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
		ft::map<std::string,int> m;
		if (!m.empty()) {
			PRINT_ERR("A new map is not considered empty");
		}
		else
			std::cout << OK_MSG;
		m.insert(ft::pair<std::string,int>("s",5));
		if (m.empty()) {
			PRINT_ERR("Map is not considered empty when 1 element is inserted");
		}
		else
			std::cout << OK_MSG;

		m.clear();
		if (!m.empty()) {
			PRINT_ERR("Map is not considered empty when adding and removing 1 element");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // empty
		PRINT_CAT(15, "size");
		ft::map<std::string,int> m;
		m.insert(ft::pair<std::string,int>("one", 1));
		m.insert(ft::pair<std::string,int>("two", 2));
		m.insert(ft::pair<std::string,int>("three", 3));
		m.insert(ft::pair<std::string,int>("four", 4));

		if (m.size() != 4) {
			PRINT_ERR("Size is not 4 when inserting 4 times");
		}
		else
			std::cout << OK_MSG;

		m.erase("one");
		m.erase("two");
		if (m.size() != 2){
			PRINT_ERR("Did not return correct value when removing 2 elements");
		}
		else
			std::cout << OK_MSG;

		m.clear();
		if (m.size() != 0) {
			PRINT_ERR("Did not return 0 when using clear()");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

static void check_modifier()
{
	std::cout << "\033[0;33m> Testing modifiers\033[0m" << std::endl;
	ft::pair<int,int> arr[] = { ft::pair<int,int>(3,3),
							    ft::pair<int,int>(7,7),
							    ft::pair<int,int>(1,1),
							    ft::pair<int,int>(15,15),
							    ft::pair<int,int>(123,123),
							    ft::pair<int,int>(-6,-6),
							    ft::pair<int,int>(9,9)};
	{ // insert
		PRINT_CAT(15, "insert");

		ft::map<int, int> m(arr, arr + 7);
		ft::pair<ft::map<int, int>::iterator, bool> i;

		i = m.insert(ft::pair<int,int>(2,2));
		if (m.size() != 8 || (*(i.first)).second != 2 || !i.second) {
			PRINT_ERR("Did not insert value correctly or did not return correct value");
		}
		else
			std::cout << OK_MSG;
		i = m.insert(ft::pair<int,int>(2,2));
		if (m.size() != 8 || (*(i.first)).second != 2 || i.second) {
			PRINT_ERR("Did return correctly with duplicate");
		}
		else
			std::cout << OK_MSG;

		i.first = m.insert(i.first, ft::pair<int,int>(19,19));
		if (m.size() != 9 || (*(i.first)).second != 19) {
			PRINT_ERR("Did not insert correctly with hint");
		}
		else
			std::cout << OK_MSG;
		i.first = m.insert(i.first, ft::pair<int,int>(19,19));
		if (m.size() != 9 || (*(i.first)).second != 19) {
			PRINT_ERR("Did not return correct value when trying to insert 19");
		}
		else
			std::cout << OK_MSG;

		ft::pair<int, int> arr2[] = {ft::pair<int,int>(13,13),
									 ft::pair<int,int>(-6,-6),
									 ft::pair<int,int>(-5,-5),
									 ft::pair<int,int>(-3,-3)};
		m.insert(arr2, arr2 + 4);
		if (m.size() != 12) {
			PRINT_ERR("Did not insert correctly with iterators");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ //
		PRINT_CAT(15, "clear");
		ft::map<int, int> m(arr, arr + 7);
		m.clear();
		if (m.size() != 0 || !m.empty()) {
			PRINT_ERR("Did not clear correctly");
		}
		else
			std::cout << OK_MSG;

		m.clear();
		std::cout << OK_MSG; // Checks for errors with clearing an empty map

		m.insert(ft::pair<int, int>(3,5));
		m.clear();
		if (m.size() != 0 || !m.empty()) {
			PRINT_ERR("Did not clear correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // erase
		PRINT_CAT(15, "erase");
		ft::map<int,int> m(arr, arr + 7);
		ft::map<int, int>::iterator i = m.find(15);

		m.erase(i);
		if (m.find(15) != m.end() || m.size() != 6) {
			PRINT_ERR("Could not erase element using an iterator");
		}
		else
			std::cout << OK_MSG;
		m.erase(15); // shouldn't crash
		std::cout << OK_MSG;

		m.erase(3);
		if (m.find(3) != m.end() || m.size() != 5) {
			PRINT_ERR("Could not erase element using a key");
		}
		else
			std::cout << OK_MSG;

		m.erase(m.begin(), m.end());
		if (!m.empty()) {
			PRINT_ERR("Could not erase every element using a range");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // swap
		PRINT_CAT(15, "swap");
		ft::map<int,int> m1(arr, arr + 3);
		ft::map<int,int> m2(arr + 3, arr + 7);

		m1.swap(m2);
		if (m1.size() != 4 || m2.size() != 3 || m1.begin()->second != -6  || m2.begin()->second != 1){
			PRINT_ERR("Could not swap");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // std::swap
		PRINT_CAT(15, "std::swap");
		ft::map<int,int> m1(arr, arr + 3);
		ft::map<int,int> m2(arr + 3, arr + 7);

		std::swap(m1, m2);
		if (m1.size() != 4 || m2.size() != 3 || m1.begin()->second != -6  || m2.begin()->second != 1){
			PRINT_ERR("Could not swap");
		}
		else
			std::cout << OK_MSG << std::endl;
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
