#include <iostream>
#include <fstream>
#include "matrix_funcs.h"

int main(int argc, char** argv)
{
  int l = argc;
  std::cout << l << "\n";
  if (l < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (l > 4)
  {
    std::cerr << "Too many arguments\n";
  }

  char* f = argv[1];
  int c = *f - '0';
  std::cout << f << "\n";
  std::cout << c << "\n";
  std::ifstream input(argv[2]);
  int m = 0, n = 0, k = 0;
  input >> m >> n;
  k = m * n;
  int* matrix = nullptr;
  try
  {
    matrix = demehin::alloc(k, c);
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }

  std::cout << k << "\n";
}


