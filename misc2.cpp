
/*
2) Write an algorithm to calculate the square root of a number.
*/
/*
n = the number whose square root has to be calculated.
sq_root = the output, ( it has to be initialized by a guessed sq_root , that must be smaller than the n);  
*/

void square_root(const double &n, double &sq_root, const double &tolerance ) {

  //validate inputs 
  if( n < 0.0 || sq_root < 0.0 ||  tolerance < 0.0 ){
     ;//To be done //throw error; 
  }

  if(sq_root>n){
   sq_root  = n/2 ; 
  }
  
  double diff = n-sq_root*sq_root;

  if(fabs(diff)<tolerance) {
    return; 
  }
  
  int factor = 1; 
  
  if(diff < 0 ){//sq_root is too large
    factor = -1; 
  }
  
  square_root(n,sq_root + factor*,tolerance); 

}

/*
3) Given an array of integers, write a method that returns an array of the same size where each index is the 
product of all integers except itself, i.e.
given array {1,2,3,4} return {24,12,8,6} explicitly {2*3*4,1*3*4,1*2*4,1*2*3}.
*/
#include <algorithm> 
#include <vector> 
#include <utility> 

using namespace std; 

double multiplies (double &a, double &b) {
  return a*b; 
}

void product_otherthan_self(const vector<int> iv, vector<int> &ov) {
  
  ov.epmty(); 
  
  const long long product = accumulate(begin(v),end(v),1,multiplies); 
  
  for (suto x: iv) {
    ov.push_back(product/x); 
  }
  
}


/*4) Give an array of 100 random integers. Write an algorithm to find the closest 2 integers (closest by position) in the array that 
add up to 100.
*/
#include <algorithm> 
#include <iostream> 
#include <cassert>

using namespace std; 

/*
Role: 
The function returns:
  true,  if input integer array contains any two elements summing to 100
  false, if input integer array does not contains any two elements summing to 100
  Note: For invalid inputs( 0 or 1 size arrays ) it will return false; 
Side effect: 
  the vector is sorted now. 
  This side effect can be easily removed if a copy of the input vector is created.  
  
Other possible enhancements:
1. For invalid inputs, it should throw errors.
2. create a template function so that if needed the function can be resused for other data-types(e.g. unsigned int , long , long long ).  
*/ 
bool AddUpTo(vector<int> &v) {

  bool AddUpToNum = false; 

  const int num = 100; 

  sort(begin(v),end(v)); 

  for (auto x: v) {
    auto it = find (begin(v),end(v),num - x);  
    if (it != v.end()){
      AddUpToNum = true;
      break; 
    }
  }

return AddUpToNum; 

}


/*
5)-+ Given the root node to a singly linked list, write an algorithm to detect if there is a loop in the list.
*/

struct Node {
  int data; 
  int *next; 
}

bool FindLoop(Node *root){

if(nullptr==root){
  //tbd ; Throw error accrding to developemtn environment
}

bool  result = false; 

Node *speed1 =  root; 
Node *speed2 =  root;  

while(speed1->next) {

   speed1 = speed1->next; 
   speed2 = speed2->next->next; 
   if(spped1==speed2){
     result = true; 
     break; 
   } 
  
}; 

return result; 

}

/*
6) Given the function: "bool numExists( int array[], int array_len, int num )" where "array" is a sorted array of integers.  Determine if "num" exists in the array.
*/
