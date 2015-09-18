////////////////////////////////////////////////////////////
///
#include <algorithm> 
#include <sstream>
#include <vector> 
#include  <cctype>

#include <Windows.h> 

#include "MnjStringUtils.h" 

vec_str MnjStringUtils::GetDifference(const vec_str &vec_from, const vec_str &vec_less){

	vec_str l_vec_from(begin(vec_from), end(vec_from));
	sort(begin(l_vec_from), end(l_vec_from));
	vec_str l_vec_less = vec_less;
	sort(begin(l_vec_less), end(l_vec_less));
	//vector<string> a;
	vec_str vec_diff(l_vec_from.size());

	auto it = std::set_difference(begin(l_vec_from), end(l_vec_from), begin(l_vec_less), end(l_vec_less), begin(vec_diff));
	vec_diff.resize(it - begin(vec_diff));

	return vec_diff;
}
std::string& MnjStringUtils::MnjLtrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from right
std::string& MnjStringUtils::MnjRtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from left & right
std::string& MnjStringUtils::MnjTrim(std::string& s, const char* t)
{
	return MnjLtrim(MnjRtrim(s, t), t);
}


double MnjStringUtils::GetNumberAfterChar(const std::string &str, const char ic){
	//Currently handles cases where 
	//str is  "Q5996=0.000000"
	//str is  "Q5996     =0.000000"

	//tbd: p2 :  throw error if 
	// 1. the separator character is not present in str 
	// 2. 'ic' 

	//N00110 Q5996 = 0.000000
	//N00120 Q5995 = 35.369198
	//N00130 Q5994 = -285.409363

	auto it = find(begin(str), end(str), '=');
	string trimmed(it + 1, end(str));
	std::string::size_type sz;
	double d = std::stod(trimmed, &sz);
	return d;

}


std::string  MnjStringUtils::ReplaceString(string &subject, const string &search, const string &replace){
	//ReplaceString(std::string subject, const std::string& search,
	//const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

auto MnjStringUtils::append_space(string x, string y)->string
{
	return x + y;
}
auto MnjStringUtils::GetIntAsString(const int  &i)->std::string{//tbd: P3 : delete the function, reaplace with tostring 

	std::ostringstream strs;
	strs << i;
	return strs.str();
}

std::string  MnjStringUtils::GetDoubleAsString(double  &d){//tbd: P3 : delete the function, reaplace with tostring 
	std::ostringstream strs;
	strs << d;
	return strs.str();
}


vector<string> MnjStringUtils::Str2VecStr(std::string &str){

	std::istringstream buffer(str);
	std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)),
		std::istream_iterator<std::string>());
	return ret;
}


vec_vec_str  MnjStringUtils::VecStr2VecVecStr(vec_str &i_vec_str){

	vec_vec_str ret_vec_vec_str;
	for (auto str : i_vec_str){
		std::istringstream buffer(str);
		std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)),
			std::istream_iterator<std::string>());
		ret_vec_vec_str.push_back(ret);
	}
	return ret_vec_vec_str;
}


int MnjStringUtils::PrependInt(vec_vec_str &ovec_vec_str, int prepend){
	//It is used to  prepend a line number at the beginning of each vector. 
	//It starts with prepeding "1" , "2" if the input prepend = 1.  


	int i = prepend;
	auto it = begin(ovec_vec_str);
	for (; it != end(ovec_vec_str); it++){

		string str = MnjStringUtils::GetIntAsString(i);
		i++;
		(*it).insert(begin(*it), str);
	}

	return 0;
}

int MnjStringUtils::PrependStr(vec_vec_str &ovec_vec_str, const string &block_prefix, int prepend){
	//It is used to  prepend a line number at the beginning of each vector. 
	//It starts with prepeding "1" , "2" if the input prepend = 1.  


	int i = prepend;
	auto it = begin(ovec_vec_str);
	for (; it != end(ovec_vec_str); it++){

		string i_as_str = to_string(i);
		string block(block_prefix + i_as_str);
		i++;
		(*it).insert(begin(*it), block);
	}

	return 0;
}



///////////////////////////////////////////////////////////////////
void MnjStringUtils::GetDoubles(vector<std::string> &ivecStr, vector<double> &oVec){
	for (string x : ivecStr) {
		double d = atof(x.c_str());
		oVec.push_back(d);
	}
}
///////////////////////////////////////////////////////////////////
void MnjStringUtils::GetDoubles(std::string &iStr, vector<double> &oVec){
	std::string s(iStr.begin() + 1, iStr.end() - 1);
	std::istringstream str_stream(s);
	std::string field;
	while (std::getline(str_stream, field, ',')) {
		double d = atof(field.c_str());
		oVec.push_back(d);
	}
}

bool MnjStringUtils::IsPrefixWordAndSuffixNum(const string &str){
	bool alpha_num = false;
	if (!str.length()){
		return alpha_num;
	}
	bool alpha = false;
	if (isalpha(str[0])){
		alpha = true;
	}
	bool num = false;
	if (alpha){
		auto it1 = find_if(begin(str), end(str), isdigit);
		if (it1 != end(str)){

			auto it2 = find_if(it1, end(str), isalpha);
			//if any aplha is found after first digit has been found, this function should return false.
			num = it2 == end(str);
		}
	}


	alpha_num = alpha && num;
	return alpha_num;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
std::string MnjStringUtils::wstrtostr(const std::wstring &wstr)

{

	// Convert a Unicode string to an ASCII string

	std::string strTo;

	char *szTo = new char[wstr.length() + 1];

	szTo[wstr.size()] = '\0';

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);

	strTo = szTo;

	delete[] szTo;

	return strTo;

}

///////////////////////////////////////////////////////////////////////////////////////////
std::wstring MnjStringUtils::strtowstr(const std::string &str)

{

	// Convert an ASCII string to a Unicode String

	std::wstring wstrTo;

	wchar_t *wszTo = new wchar_t[str.length() + 1];

	wszTo[str.size()] = L'\0';

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());

	wstrTo = wszTo;

	delete[] wszTo;

	return wstrTo;

}
