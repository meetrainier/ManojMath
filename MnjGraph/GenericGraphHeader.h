#pragma once
#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <random>
#include <stack> 
#include <string> 

#define LINUX_KEY

#ifdef LINUX_KEY
#define NEWLINE "\n"
#elif WINDOWS_KEY
#define NEWLINE "\r\n"
#endif

extern void TestshortestChainLen(); 

class IllegalArgumentException : public std::exception
{
  std::string str;
public:
  IllegalArgumentException(const std::string is)
  {
    str = is;
  }

  virtual const char* what() const throw()
  {
    return str.c_str();
  }
};
