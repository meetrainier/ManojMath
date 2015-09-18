#pragma once 
#include <string> 
#include <vector> 
#include "MnjMathNamespace.h"   //vec_str 

using namespace std;
using namespace MnjMath;

#define MNJ_FILE_PATH_SIZE  1024  

class MnjStringUtils{

public:
	static std::string& MnjLtrim(std::string& s, const char* t = " \t\n\r\f\v");
	static std::string& MnjRtrim(std::string& s, const char* t = " \t\n\r\f\v");
	static std::string& MnjTrim(std::string& s, const char* t = " \t\n\r\f\v");
	static auto append_space(string x, string y)->string;
	static int PrependStr(vec_vec_str &ovec_vec_str, const string &block_prefix, int prepend);

	static bool IsPrefixWordAndSuffixNum(const string &str);

	static std::string  GetDoubleAsString(double  &d);

	static  auto GetIntAsString(const int &d)->std::string;

	//Split a string into vector of string (based on white spaces).
	static vector<string> Str2VecStr(std::string &str);

	//Each string of the input vector is split( whitespace field separator)  into a vector of string.   
	static vec_vec_str  VecStr2VecVecStr(vec_str &str);

	///////////////////////////////////////////////////////////////////
	static void GetDoubles(vector<std::string> &ivecStr, vector<double> &oVec);
	///////////////////////////////////////////////////////////////////
	static void GetDoubles(std::string &iStr, vector<double> &oVec);

	//It is used to  prepend a line number at the beginning of each vector. 
	//It starts with prepeding "1" , "2" if the input prepend = 1.  
	static int PrependInt(vec_vec_str &vecVecStr, int);

	//static void ReplaceAll(string &s, const string &search, const string &replace);
	static std::string ReplaceString(string &s, const string &search, const string &replace);
	static double GetNumberAfterChar(const std::string &str, const char ic);

	static std::wstring strtowstr(const std::string &str);
	static std::string wstrtostr(const std::wstring &wstr);
	static vec_str GetDifference(const vec_str &vec_from, const vec_str &vec_less);
};
