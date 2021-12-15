// Example program
#include <algorithm> 
#include <iostream> 
#include <cassert>

using namespace std; 

/*

Role: 

The function returns:
  true,  if input integer array contains any two elements summing to 42
  false, if input integer array does not contains any two elements summing to 42
  Note: For invalid inputs( 0 or 1 size arrays ) it will return false; 

Side effect: 
  the vector is sorted now. 
  This side effect can be easily removed if a copy of the input vector is created.  
  
Other possible enhancements:
1. For invalid inputs, it should throw errors.
2. create a template function so that if needed the function can be resused for other data-types(e.g. unsigned int , long , long long ).  

*/ 
bool AddUpTo(vector<int> &v) {

  bool AddUpTo42 = false; 

  const int num = 42; 

  sort(begin(v),end(v)); 

  for (auto x: v) {
    auto it = find (begin(v),end(v),num - x);  
    if (it != v.end()){
      AddUpTo42 = true;
      break; 
    }
  }

return AddUpTo42; 

}


void Test_1() {

  vector<int> v; 
  bool result = AddUpTo(v); 
  assert(false == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 
  
}

void Test0() {

  vector<int> v({1}); 
  bool result = AddUpTo(v); 
  assert(false == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 
  
}

void Test1() {

  vector<int> v({1,2,3}); 
  bool result = AddUpTo(v); 
  assert(false == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 
  
}

void Test2() {

  vector<int> v({42,2,43}); 
  bool result = AddUpTo(v); 
  assert(false == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 

}

void Test3() {

  vector<int> v({1,2,42}); 
  bool result = AddUpTo(v); 
  assert(false == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 

}


void Test4() {

  vector<int> v({42,0,1}); 
  bool result = AddUpTo(v); 
  assert(true == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 

}

void Test5() {

  vector<int> v({1,0,42}); 
  bool result = AddUpTo(v); 
  assert(true == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 

}

void Test6() {

  vector<int> v({1,43,-1,1}); 
  bool result = AddUpTo(v); 
  assert(true == result); 
  cout << __FUNCTION__ <<   " Success" << endl; 

}
//void TestAddUpTo() {
 int main() {

  Test_1();   
  Test0(); 

//Test False condition 
  Test1(); 
  Test2(); 
  Test3();
  
//Test True condition   

  Test4(); 
  Test5(); 
  Test6();
  
  return 0;
}
