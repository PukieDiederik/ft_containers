#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <iomanip>

#define PRINT_ERR(MSG) std::cout << "\033[0;31m KO.\033[0m" << std::endl; std::cerr << "\033[0;31m"MSG"\n\033[0m"
#define OK_MSG "\033[0;32mOK. \033[0m"
#define PRINT_CAT(WIDTH,MSG) std::cout << std::left << std::setw(WIDTH) << MSG << ": "

void	vector_test();
void	stack_test();

#endif
