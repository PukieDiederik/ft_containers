#include "test.hpp"
#include "vector.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

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

	ft::vector<int> v;
	v.push_back(5);
	v.push_back(9);
	v.push_back(12);

	{ // begin
		PRINT_CAT(15, "begin");
		ft::vector<int>::iterator it = v.begin();
		if (&*it != v.data()) {
			PRINT_ERR("Begin iterator does dereference to first element");
		}
		else
			std::cout << OK_MSG;

		++it;
		if (&*it != v.data() + 1) {
			PRINT_ERR("++Begin iterator does dereference to second element");
		}
		else
			std::cout << OK_MSG;

		++it;
		if (&*it != v.data() + 2) {
			PRINT_ERR("Begin + 2 does derefernce to second element");
		}
		else
			std::cout << OK_MSG;

		++it;
		if (it != v.end() || v.begin() + 3 != v.end()) {
			PRINT_ERR("Begin + 3 does not equal end()");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // end
		PRINT_CAT(15, "end");

		ft::vector<int>::iterator it = v.end();
		if (&*it != v.data() + 3) {
			PRINT_ERR("end iterator does not equal 1 past amount of elements");
		}
		else
			std::cout << OK_MSG;

		--it;
		if (&*it != v.data() + 2) {
			PRINT_ERR("--end iterator does dereference to second element");
		}
		else
			std::cout << OK_MSG;
		it--;

		if (it - 1 != v.begin()) {
			PRINT_ERR("end - 3 does not equal begin()");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // rbegin
		PRINT_CAT(15, "rbegin");

		ft::vector<int>::reverse_iterator it = v.rbegin();
		if (&*(v.end() - 1) != &*it) {
			PRINT_ERR("reverse iterator does not point to last object");
		}
		else
			std::cout << OK_MSG;
		it++;
		if (&*it != v.data() + 1) {
			PRINT_ERR("reverse iterator does not deference correctly");
		}
		else
			std::cout << OK_MSG;
		it += 2;

		if (it != v.rend() || &*it != &*(v.begin() - 1)) {
			PRINT_ERR("iterator does not match end");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // rend
		PRINT_CAT(15, "rend");

		ft::vector<int>::reverse_iterator it = v.rend();
		if (&*(v.begin() - 1) != &*it) {
			PRINT_ERR("reverse iterator does not point to last object");
		}
		else
			std::cout << OK_MSG;
		it--;
		if (&*it != &*v.begin()) {
			PRINT_ERR("reverse iterator does not deference correctly");
		}
		else
			std::cout << OK_MSG;
		it -= 3;
		if (it != v.rbegin() - 1 || &*it != &*(v.end())) {
			PRINT_ERR("iterator does not match end");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
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
	ft::vector<int> v_b(10, 5);
	{ // reserve
		PRINT_CAT(15, "reserve");
		ft::vector<int> v(v_b);
		v.reserve(25);
		if (v.capacity() != 25 || v.size() != 10) {
			PRINT_ERR("Did not reserve correct amount of memory");
		}
		else
			std::cout << OK_MSG;

		v.reserve(5);
		if (v.capacity() != 25 || v.size() != 10) {
			PRINT_ERR("Should not have reserved memory");
		}
		else
			std::cout << OK_MSG;

		v.reserve(27);
		if (v.capacity() != 27 || v.size() != 10) {
			PRINT_ERR("Did not reserve enough memory");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // Shrink_to_fit
		PRINT_CAT(15, "shrink to fit");
		ft::vector<int> v(v_b);
		v.shrink_to_fit();
		if (v.capacity() != v.size()) {
			PRINT_ERR("Did not shrink memory correctly");
		}
		else
			std::cout << OK_MSG;

		v.push_back(2);
		v.shrink_to_fit();
		if (v.capacity() != v.size()) {
			PRINT_ERR("Did not shrink memory correctly");
		}
		else
			std::cout << OK_MSG;

		v.shrink_to_fit();
		if (v.capacity() != v.size()) {
			PRINT_ERR("Did not shrink memory correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // resize
		PRINT_CAT(15, "resize");
		ft::vector<int> v(v_b);
		v.resize(25);
		if (v.size() != 25) {
			PRINT_ERR("Did not resize correctly");
		}
		else
			std::cout << OK_MSG;

		v.resize(5);
		if (v.size() != 5) {
			PRINT_ERR("Did not resize to smaller amount correctly");
		}
		else
			std::cout << OK_MSG;

		v.resize(7, 19);
		if (v.size() != 7 || v[6] != 19) {
			PRINT_ERR("Did not fill with correct value");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // clear
		PRINT_CAT(15, "clear");
		ft::vector<int> v(v_b);
		v.clear();
		if (v.size() != 0) {
			PRINT_ERR("Did not clear correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

// Checks if regular manipulation functions work
static void check_manip()
{
	std::cout << "\033[0;33m> Testing manipulation\033[0m" << std::endl;
	int arr[] = {5, 1, 19, 12, 0, 8};
	{ // insert
		PRINT_CAT(15, "insert");
		ft::vector<int> v(arr, arr + 6);

		v.insert(v.begin() + 3, 999);
		if (v.size() != 7 || v[3] != 999 || v[6] != 8 || v[4] != 12) {
			PRINT_ERR("Did not insert value in the middle correctly");
		}
		else
			std::cout << OK_MSG;
		v.insert(v.end(), 123);
		if (v.size() != 8 || v[7] != 123) {
			PRINT_ERR("Did not insert at end correctly");
		}
		else
			std::cout << OK_MSG;
		v.insert(v.begin(), 5, 45);
		if (v.size() != 13 || v[0] != 45 || v[4] != 45) {
			PRINT_ERR("Could not insert multiple values correctly");
		}
		else
			std::cout << OK_MSG;
		int a[] = {3, 9, 20};
		v.insert(v.begin() + 1, a, a + 3);
		if (v.size() != 16 || v[1] != 3 || v[2] != 9 || v[3] != 20) {
			PRINT_ERR("Could not insert with iterators correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // erase
		PRINT_CAT(15, "erase");
		ft::vector<int> v(arr, arr + 6);

		v.erase(v.begin() + 1);
		if (v.size() != 5 || v[0] != 5 || v[1] != 19) {
			PRINT_ERR("Could not erase single element");
		}
		else
			std::cout << OK_MSG;

		v.erase(v.begin(), v.end());
		if (v.size() != 0 || !v.empty()) {
			PRINT_ERR("Did not erase entire array");
		}
		else
			std::cout << OK_MSG;

		v.assign(arr, arr + 6);
		v.erase(v.begin() + 1, v.end() - 1);
		if (v.size() != 2 || v[0] != 5 || v[1] != 8) {
			PRINT_ERR("Did not erase multiple elements correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // push_back
		PRINT_CAT(15, "push_back");
		ft::vector<int> v;

		v.push_back(3);
		if (v.size() != 1 || v[0] != 3){
			PRINT_ERR("Could not push a value to an empty vector");
		}
		else
			std::cout << OK_MSG;
		v.push_back(17);
		if (v.size() != 2 || v[0] != 3 || v[1] != 17) {
			PRINT_ERR("Could not push to non-empty vector");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // pop_back
		PRINT_CAT(15, "pop_back");
		ft::vector<int> v(arr, arr + 6);

		v.pop_back();
		if (v.size() != 5 || v[4] != 0) {
			PRINT_ERR("Did not pop correctly");
		}
		else
			std::cout << OK_MSG;
		v.pop_back();
		if (v.size() != 4 || v[3] != 12) {
			PRINT_ERR("Did not pop correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

// Check functions that didn't fit in another category
static void check_other()
{
	std::cout << "\033[0;33m> Testing other\033[0m" << std::endl;
	ft::vector<int> v1_b;
	ft::vector<int> v2_b;

	v1_b.push_back(1);
	v1_b.push_back(2);
	v1_b.push_back(3);

	v2_b.push_back(4);
	v2_b.push_back(5);
	v2_b.push_back(6);
	v2_b.push_back(7);
	{ // std::swap
		PRINT_CAT(15, "std::swap");
		ft::vector<int> v1(v1_b);
		ft::vector<int> v2(v2_b);

		std::swap(v1, v2);
		if (v1.size() != 4 || v2.size() != 3 || v1[0] != 4 || v1[3] != 7 || v2[0] != 1 || v2[2] != 3) {
			PRINT_ERR("Did not swap correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ //swap
		PRINT_CAT(15, "swap");
		ft::vector<int> v1(v1_b);
		ft::vector<int> v2(v2_b);

		v1.swap(v2);
		if (v1.size() != 4 || v2.size() != 3 || v1[0] != 4 || v1[3] != 7 || v2[0] != 1 || v2[2] != 3) {
			PRINT_ERR("Did not swap correctly");
		}
		else
			std::cout << OK_MSG;

		ft::vector<int>().swap(v1);
		if (!v1.empty() || v1.capacity() != 0 || v1.data() != NULL){
			PRINT_ERR("did not swap correctly with NULL vector");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{
		PRINT_CAT(15, "assign");
		ft::vector<int> v1(v1_b);
		ft::vector<int> v2;

		v1.assign(15, 5);
		if (v1.size() != 15 || v1[3] != 5 || v1[14] != 5) {
			PRINT_ERR("Did not assign correctly");
		}
		else
			std::cout << OK_MSG;
		v2.assign(4, -3);
		if (v2.size() != 4 || v2[3] != -3 || v2[0] != -3) {
			PRINT_ERR("Did not assign correctly with empty vector");
		}
		else
			std::cout << OK_MSG;
		v2.clear();

		v2.assign(v1.begin(), v1.end() - 3);
		if (v2.size() != 12 || v2[5] != 5 || v2[11] != 5) {
			PRINT_ERR("Could Not assign correctly with an iterator");
		}
		else std::cout << OK_MSG << std::endl;
	}
}

void vector_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mvector" << std::endl;

	check_construction();
	check_accessor();
	check_iterator();
	check_manip();
	check_size_manip();
	check_other();
	check_comparison();
}