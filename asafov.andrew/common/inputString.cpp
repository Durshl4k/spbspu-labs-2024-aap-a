#include "inputString.hpp"
#include <iostream>
#include <cstddef>
#include "increaseString.hpp"

char* asafov::inputString()
{
  size_t reallength = 0;
  size_t possiblelength = 1;
  char* string = new char[possiblelength];
  char ch = 0;
  while (!std::cin.eof())
  {
    possiblelength--;
    std::cin >> ch;
    if (std::cin.fail() || std::cin.eof())
    {
      string[reallength] = '\0';
      break;
    }
    string[reallength] = ch;
    reallength++;
    if (possiblelength == 0)
    {
      possiblelength = reallength;
      char* newstring = nullptr;
      try
      {
        newstring = increaseString(string, reallength, reallength);
      }
      catch (const std::bad_alloc& e)
      {
        delete[] string;
        throw e;
      }
      delete[] string;
      string = newstring;
    }
  }
  if (reallength == 0)
  {
    string[0] = 0;
  }
  return string;
}
