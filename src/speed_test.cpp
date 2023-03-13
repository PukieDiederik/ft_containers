#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>

#define TEST_SIZE 10000

#if STD==1

#include <vector>
#include <stack>
#include <map>

namespace ft = std;

#else

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

#endif

int main()
{
	std::cout << std::fixed;

	{
		clock_t total = 0;
		clock_t start;
		clock_t end;

		std::cout << "\033[0;36m>>> Testing Vector <<<\033[0m" << std::endl;
		ft::vector<std::string> v;
		ft::vector<std::string> w;

		// Testing push_back
		std::cout << "\033[0;32mpush_back: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			v.push_back("Hello");
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;32mclear: \033[0m";
		start = clock();
		v.clear();
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		// Testing insert
		std::cout << "\033[0;32minsert: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			v.insert(v.begin(), "Hello");
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		// Testing insert
		std::cout << "\033[0;32moperator[]: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			v[i];
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		w = v;

		std::cout << "\033[0;32mpop_back: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			v.pop_back();
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;32merase: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			w.erase(w.begin());
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;33mTotal time\033[0m: " << total << " ("\
			<< (((double)total)/CLOCKS_PER_SEC)<< "S)\n" << std::endl;
	}
	{
		std::cout << "\033[0;36m>>> Testing Stack <<<" << std::endl;
		clock_t total = 0;
		clock_t start;
		clock_t end;

		ft::stack<std::string> s;

		std::cout << "\033[0;32mpush: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			s.push("Hello");
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;32mpop: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			s.push("Hello");
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;33mTotal time\033[0m: " << total << " ("\
			<< (((double)total)/CLOCKS_PER_SEC)<< "S)\n" << std::endl;
	}
	{
		std::cout << "\033[0;36m>>> Testing map <<<" << std::endl;
		clock_t total = 0;
		clock_t start;
		clock_t end;

		ft::map<int, std::string> m;
		ft::map<int, std::string> n;
		int keys[TEST_SIZE];

		std::srand(0);

		std::cout << "\033[0;32minsert: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			keys[i] = std::rand();
			m.insert(ft::pair<int, std::string>(keys[i], "Hello"));
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;32mfind: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			m.find(keys[i]);
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		n = m;

		std::cout << "\033[0;32merase: \033[0m";
		start = clock();
		for(int i = 0; i < TEST_SIZE; ++i)
		{
			m.erase(keys[i]);
		}
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;

		std::cout << "\033[0;32mclear: \033[0m";
		start = clock();
		n.clear();
		end = clock();
		total += end - start;
		std::cout << end - start << " (" << (((double)end - (double)start)/CLOCKS_PER_SEC)<< "S)" << std::endl;


		std::cout << "\033[0;33mTotal time\033[0m: " << total << " ("\
			<< (((double)total)/CLOCKS_PER_SEC)<< "S)\n" << std::endl;
	}
}

