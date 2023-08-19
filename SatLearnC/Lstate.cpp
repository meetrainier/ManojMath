#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <iostream>

static std::map<const std::string, const std::string> map_state_to_capital
={
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

void GetInputs(const std::string &str, std::string &given_answer)
{
  //Get the user's inputs.
  std::cout << str << ": ";
  std::getline(std::cin, given_answer);
  std::cout << std::endl;
}

//The procedure name is HandleGivenAnswer.
//The parameters that have an effect on the functionality are "str" and "given_answer".
//Strings are lists of characters.In this program we iterate through two lists and compare 
//the corresponding elements of the lists.As the list are strings, its elements are characters.
//The comparison is done in a case-insensitive manner by first converting the characters to 
//lower cases.
void HandleGivenAnswer(const std::string& str, const std::string& given_answer, int& terminate)
{
  const std::string period(".");
  //check if the given_answer is a period. 
  if (std::equal(begin(period), end(period),
        begin(given_answer), end(given_answer),
        [](char a, char b) {
          return tolower(a) == tolower(b);
        }))
  {
    terminate = 1;
    return;
  }
  //if the given answer is not a period, does it match with the correct answer?  
  else if (!std::equal(begin(str), end(str),
    begin(given_answer), end(given_answer),
    [](char a, char b) {
      return tolower(a) == tolower(b);
    }))
  {
    //If it does not match with the correct answer, report that it is incorrect. 
    std::cout << "Incorrect!" << std::endl;
    std::cout << "The correct answer is:" << str << std::endl << std::endl;
  }
}

//int main(char** argv, int argc)
//{
//  std::cout << "This program provides you the name of a state. You are " << std::endl;
//  std::cout << "supposed to enter the name of the corresponding capital." << std::endl;
//  std::cout << "To Terminate the program, enter \".\"" << std::endl;
// 
//  //Here each element of the list is accessed. 
//  for (auto& m : map_state_to_capital)
//  {
//    std::string given_answer;
//    GetInputs(m.second ,given_answer);
//    int terminate = 0;
//    HandleGivenAnswer(m.first, given_answer, terminate);
//    if (terminate)
//    {
//      std::cout << "Exiting..." << std::endl;
//      break;
//    }
//  }//for loop ends 
//
//  return 0;
//}