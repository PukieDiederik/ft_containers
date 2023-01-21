#include "test.hpp"
#include "stack.hpp"
#include <iostream>

static void check_other()
{
	std::cout << "\033[0;33m> Testing other\033[0m" << std::endl;
	ft::stack<int> s;
	// push pop top
	{ // push
		PRINT_CAT(15, "push");
		s.push(123);
		if (s.size() != 1 || s.top() != 123) {
			PRINT_ERR("Did not push correctly");
		}
		else
			std::cout << OK_MSG;

		s.push(19);
		if (s.size() != 2 || s.top() != 19) {
			PRINT_ERR("Did not push correctly");
		}
		else
			std::cout << OK_MSG;

		s.push(-230);
		if (s.size() != 3 || s.top() != -230) {
			PRINT_ERR("Did not push correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // pop
		PRINT_CAT(15, "pop");
		s.pop();
		if (s.size() != 2 || s.top() != 19) {
			PRINT_ERR("Did not push correctly");
		}
		else
			std::cout << OK_MSG;

		s.pop();
		if (s.size() != 1 || s.top() != 123) {
			PRINT_ERR("Did not push correctly");
		}
		else
			std::cout << OK_MSG;

		s.pop();
		if (!s.empty()) {
			PRINT_ERR("Did not pop correctly with a size 1 stack");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // top
		PRINT_CAT(15, "top");
		s.push(5);
		s.push(9);
		if (s.top() != 9) {
			PRINT_ERR("top does not return correct value");
		}
		else
			std::cout << OK_MSG;
		s.pop();
		if (s.top() != 5) {
			PRINT_ERR("top does not return correct value");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

// Checks if the constructors work as expected
static void check_construction()
{
	std::cout << "\033[0;33m> Testing construction\033[0m" << std::endl;
	ft::vector<int> v1;

	v1.push_back(3);
	v1.push_back(6);
	v1.push_back(-15);

	{ // Default construction
		PRINT_CAT(15, "default");
		ft::stack<int> s;
		if (s.size() != 0 || !s.empty()) {
			PRINT_ERR("Size of default is not correct");
		}
		else
			std::cout << OK_MSG;

		ft::stack<int> s2(v1);
		if (s2.size() != 3 || s2.top() != -15) {
			PRINT_ERR("Did not construct from underlying collection correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // Copy construction
		PRINT_CAT(15, "copy");
		ft::stack<int> s(v1);
		ft::stack<int> s2(s);

		if (s2.size() != 3 || s2.top() != -15) {
			PRINT_ERR("Could not copy construct");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
	{ // copy assignment
		PRINT_CAT(15, "copy-assignment");
		ft::stack<int> s(v1);
		ft::stack<int> s2;

		s2 = s;
		if (s2.size() != 3 || s2.top() != -15) {
			PRINT_ERR("Could not copy assign correctly");
		}
		else
			std::cout << OK_MSG << std::endl;
	}
}

// Checks if comparison operators work as expected
static void check_comparison() {
	std::cout << "\033[0;33m> Testing comparison\033[0m" << std::endl;
	ft::stack<int> v1;
	ft::stack<int> v2;
	ft::stack<int> v3;
	ft::stack<int> v4;

	v1.push(1);
	v1.push(2);
	v1.push(3);

	v2.push(1);
	v2.push(2);
	v2.push(4);

	v3.push(1);
	v3.push(3);
	v3.push(3);

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

void stack_test()
{
	std::cout << "\033[0;36m>>>>> Testing \033[0mstack" << std::endl;

	check_construction();
	check_other();
	check_comparison();
}