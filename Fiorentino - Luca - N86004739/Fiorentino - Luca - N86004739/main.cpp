
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main()
{
  std::cout << "LASD Libraries 2025" << std::endl;
  std::cout << "Type 1 for lasdtest()" << std::endl;

  lasd::Vector<int> v1(10);

  int i;
  v1.Map(
    [&i](int& dat)
    {
      dat = i++;
    }
  );

  std::cout << "Traverse vector" <<  std::endl;
 
  v1.Traverse(
    [](const int& dat)
    {
      std::cout << dat;
      std::cout << ", ";
    }
  );

  std::cout << "fine" <<  std::endl;

  lasd::SetVec s1 (v1);

  std::cout << "Traverse set" <<  std::endl;

  s1.Traverse(
    [](const int& dat)
    {
      std::cout << dat;
      std::cout << ", ";
    }
  );

  std::cout << "fine" <<  std::endl;

  std::cout << "Traverse as vector set" <<  std::endl;

  s1.Vector::Traverse(
    [](const int& dat)
    {
      std::cout << dat;
      std::cout << ", ";
    }
  );
  
  std::cout << "fine" <<  std::endl;

  s1.EnsureCapacity(s1.Size()+10);
  s1.Shift(5, -10);

  std::cout << "Traverse set" <<  std::endl;

  s1.Traverse(
    [](const int& dat)
    {
      std::cout << dat;
      std::cout << ", ";
    }
  );

  std::cout << "fine" <<  std::endl;

  std::cout << "Traverse as vector set" <<  std::endl;

  s1.Vector::Traverse(
    [](const int& dat)
    {
      std::cout << dat;
      std::cout << ", ";
    }
  );
  
  std::cout << "fine" <<  std::endl;



  // std::string ans;
  // std::getline(std::cin, ans); // Legge tutta la riga, anche vuota
  // switch(ans.back())
  // {
  //   case '1':
  //     lasdtest();
  //     break;
  //   default:
  //     mytest();
  // }
  return 0;
}

