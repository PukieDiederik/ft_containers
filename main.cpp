#include "map.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
/*  ft::map<int,int> a;

  for(int i = 0; i < 100; ++i)
  {
	a.insert(ft::pair<int,int>(rand(),rand()));
  }*/

  ft::map<int,std::string> b;
 
  b.insert(ft::pair<int, std::string>(4, "Hello!"));
  b.insert(ft::pair<int, std::string>(5, "World!"));


  for(auto i = b.begin(); i != b.end(); ++i){
	std::cout << "K: " << i->first << ", V: " << i->second << std::endl;
  }
}
