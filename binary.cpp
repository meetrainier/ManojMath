// Example program
//This file is a collection of common problems involving binary form 

#include <iostream>
#include <string>
using namespace std; 

//convert goven string to biary format.
void  get_binary(int n, string &s) {
    
    while(n){
        
        if ( 0== n% 2 ) {
          s.append("1");
        }else{
             s.append("0");
        }
        
        n/=2;
    }
}
    /* Function to get no of set bits in binary
   representation of passed binary no. */
int countSetBits(int n)
{
    unsigned int count = 0;
    while (n)
    {
      n &= (n-1) ;
      count++;
    }
    return count;
}
 /*
 Given  in integer find it bianry gap 
  */
  
void  get_binary_gap(int n, int &gap) {
  //To be implemented
    bool gap_started = false; 
    
    while(n){
        
        if ( 0== n% 2 ) {
         gap_started = true;
          //1
        }else{
           //0
        }
        
        n/=2;
    }
}
    
    
//numbers of ones in a binary number 


//montgomery algorithm 
    


void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void clearScreen();
std::string validateEntry();
std::string decimalToBin(int number);
int binaryToDec(std::string number);
 
int mongomery_multiplication()
{
    clearScreen();
//takes two numbers in binary form and find their montgomery  multiplication. 

    std::cout << "Enter First Binary Number: ";
    std::string binaryString1 = validateEntry();
    int binaryNum1 = binaryToDec(binaryString1);
 
    std::cout << "Enter Second Binary Number: ";
    std::string binaryString2 = validateEntry();
    int binaryNum2 = binaryToDec(binaryString2);
    
    std::vector<int> partials(binaryString2.length(), 0);
    
    int bitShift = 0;
    int total = 0;
    for (int i = (binaryString2.length() - 1); i >= 0; i--)
    {
        if (binaryString2.compare(i, 1, "1") == 0)
        {
            partials[bitShift] = binaryNum1<<bitShift;
        }
        else
            partials[bitShift] = 0;
        
        total += partials[bitShift];
        bitShift++;
    }
    
    std::string totalStr = decimalToBin(total);
    total = totalStr.length();
    
    clearScreen();
    
    std::cout << std::fixed
              << std::setw(total) << binaryString1 << "\n"
              << std::setw(total) << binaryString2 << "\n";
    
    for (int i = 0; i < total; i++)
        std::cout << "-";
    std::cout << "\n";
    
    int zeroBuf = binaryString1.length() - 1;
    for (int i = 0; i < (binaryString2.length()); i++)
    {
        std::string tempStr = decimalToBin(partials[i]);
        if (tempStr.length() == 1)
        {
            for (int j = 0; j < zeroBuf; j++)
                tempStr += "0";
        }
        
        zeroBuf++;
        
        std::cout << std::fixed << std::setw(total)
                  << tempStr << "\n";
    }
    for (int i = 0; i < total; i++)
        std::cout << "=";
    std::cout << std::fixed << "\n"
              << std::setw(total) << totalStr << "\n\n";
}

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

std::string validateEntry()
{
    bool valid = true;
    std::string tempStr;
    
    do
    {
        valid = true;
        getline(std::cin, tempStr);
        for (int i = 0; i < tempStr.length(); i++)
        {
            if ((tempStr.compare(i, 1, "0") != 0) && (tempStr.compare(i, 1, "1") != 0))
            {
                valid = false;
                clearScreen();
                std::cout << "Enter Valid Binary Number: ";
                break;
            }
        }
    } while (valid == false);
    
    clearScreen();
    return tempStr;
}

std::string decimalToBin(int number)
{//helper finction 
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";
    
    if ( number % 2 == 0 )
        return decimalToBin(number / 2) + "0";
    else
        return decimalToBin(number / 2) + "1";
}

int binaryToDec(std::string number)
{//helper function 
    int result = 0, pow = 1;
    for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (number[i] - '0') * pow;
    
    return result;
}

int TestBinary()
{//supposed to test all  functions in this file
    
    //repsenting in hex
    
    {//make it a separate function 
    int oct = 010;
    int x = oct;
    int h = 0x0;
    h = oct;
    
    cout <<  "oct = " <<  oct << endl;
    cout <<  "x = " <<  x << endl;
    cout <<  "h = " << h << endl;
    }
    ///
    string s;
    get_binary(10, s) ;
    cout << "bianry form " << s << endl;
    
    ///
    clearScreen();
    
  std::string name;
  std::cout << "What is your name? ";
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
}
