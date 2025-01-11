#include <iostream>
#include <ios>
#include <str_input.hpp>
#include "is_expression.hpp"

int main()
{
  size_t capacity = 2;
  const char * str = dirti::str_input(std::cin, capacity);
  if (!str)
  {
    std::cerr << "Incorrect input" << "\n";
    return 1;
  }
  std::cout << std::boolalpha << dirti::is_expression(str);
}
