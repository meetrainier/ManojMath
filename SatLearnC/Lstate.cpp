#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <iostream>

static std::map<const std::string, const std::string> map_state_to_capital
= {
  {"Montgomery","Alabama"},
  {"Juneau" , "Alaska"},
  {"Phoenix" , "Arizona"},
  {"Little Rock" , "Arkansas"},
  {"Sacramento" , "California"},
  {"Denver" , "Colorado"},
  {"Hartford" , "Connecticut"},
  {"Dover" , "Delaware"},
  {"Tallahassee" , "Florida"},
  {"Atlanta" , "Georgia"},
{"Honolulu" , "Hawaii"},
{"Boise" , "Idaho"},
{"Springfield" , "Illinois"},
{"Indianapolis" , "Indiana"},
{"Des Moines" , "Iowa"},
{"Topeka" , "Kansas"},
{"Frankfort" , "Kentucky"},
{"Baton Rouge" , "Louisiana"},
{"Augusta" , "Maine"},
{"Annapolis" , "Maryland"},
{"Boston" , "Massachusetts"},
{"Lansing" , "Michigan"},
{"Saint Paul" , "Minnesota"},
{"Jackson" , "Mississippi"},
{"Jefferson City" , "Missouri"},
{"Helena" , "Montana"},
{"Lincoln" , "Nebraska"},
{"Carson City" , "Nevada"},
{"Concord" , "New Hampshire"},
{"Trenton" , "New Jersey"},
{"Santa Fe" , "New Mexico"},
{"Albany" , "New York"},
{"Raleigh" , "North Carolina"},
{"Bismarck" , "North Dakota"},
{"Columbus" , "Ohio"},
{"Oklahoma City" , "Oklahoma"},
{"Salem" , "Oregon"},
{"Harrisburg" , "Pennsylvania"},
{"Providence" , "Rhode Island"},
{"Columbia" , "South Carolina"},
{"Pierre" , "South Dakota"},
{"Nashville" , "Tennessee"},
{"Austin" , "Texas"},
{"Salt Lake City" , "Utah"},
{"Montpelier" , "Vermont"},
{"Richmond" , "Virginia"},
{"Olympia" , "Washington"},
{"Charleston" , "West Virginia"},
{"Madison" , "Wisconsin"},
{"Cheyenne" , "Wyoming"}

};

bool iequals(const std::string& a, const std::string& b)
{
  return std::equal(begin(a), end(a),
    begin(b), end(b),
    [](char a, char b) {
      return tolower(a) == tolower(b);
    });
}

void HandleGivenAnswer(const std::string& str, const std::string& given_answer, int &terminate)
{
  if (iequals(".", given_answer))
  {
    terminate = 1;
    return;
  }
  else if (!iequals(str, given_answer))
  {
    std::cout << "Incorrect!" << std::endl;
    std::cout << "The correct answer is:" << str << std::endl << std::endl;
  }

}

int main(char** argv, int argc)
{
  std::cout << "This program provides you the name of a state. You are " << std::endl;
  std::cout << "supposed to enter the name of the corresponding capital." << std::endl;
  for (auto& m : map_state_to_capital)
  {
    std::string given_answer;
    std::cout << m.second << ": "; 
    //std::cin >> given_answer;
    std::getline(std::cin, given_answer);
    std::cout << std::endl;
    int terminate = 0;
    HandleGivenAnswer(m.first, given_answer, terminate);
    if (terminate)
    {
      std::cout << "Exiting..." << std::endl;
      break;
    }

  
  }



}