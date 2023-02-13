#pragma once
//copyright(c) 2009- 2016 Manoj Lnu 
#include <string>
/*
Uses non statndard __FUNCTION__
 and itoa;

*/
namespace Mnj {


 class ErrorUtils{
  public:
 static void CreateErrorString(const char *file, int line_no,const char *func, std::string &imsg,std::string &s) {
  
  s.append("File: ");
  s.append(file);

  char buffer[100];
  _itoa_s(line_no,buffer,sizeof(buffer),10);
  
  s.append("\tLine: ");
  s.append(buffer);
  
  s.append("\tMethod: ");
  s.append(func);
  
  s.append("\tMessage: ");
  s.append(imsg);

 }

};//class ErrorUtils Ends

}