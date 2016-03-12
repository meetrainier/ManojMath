
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



/*
5)-+ Given the root node to a singly linked list, write an algorithm to detect if there is a loop in the list.
*/
/*
6) Given the function: "bool numExists( int array[], int array_len, int num )" where "array" is a sorted array of integers.  Determine if "num" exists in the array.
*/