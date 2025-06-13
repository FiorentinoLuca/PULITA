
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main()
{
  std::cout << "LASD Libraries 2025" << std::endl;
  std::cout << "Type 1 for lasdtest()" << std::endl;

  std::string ans;
  std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
  switch(ans.back())
  {
    case '1':
      lasdtest();
      break;
    default:
      mytest();
  }
  return 0;
}

