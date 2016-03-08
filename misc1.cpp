/*
1) You have a ladder n-steps in height.  You can either take one step or two steps up the ladder at a time.  
How can you find out all the different combinations up the ladder?  
Then figure out an algorithm that will actually print out all the different ways up the ladder. 
ie: 1,1,2,1,2,2... etc...

2) Write an algorithm to calculate the square root of a number.

3) Given an array of integers, write a method that returns an array of the same size where each index is the product of all integers except itself, i.e.
given array {1,2,3,4} return {24,12,8,6} explicitly {2*3*4,1*3*4,1*2*4,1*2*3}.

4) Give an array of 100 random integers. Write an algorithm to find the closest 2 integers (closest by position) in the array that 
add up to 100.

5) Given the root node to a singly linked list, write an algorithm to detect if there is a loop in the list.

6) Given the function: "bool numExists( int array[], int array_len, int num )" where "array" is a sorted array of integers.  Determine if "num" exists in the array.
*/
bool FindLastAndRemove(vector<v> , char c) {


}

bool Pop1sAndPushBack2(vector<int> &v){

bool a = FindLastAndRemove(v,'1'); 
bool b = FindLastAndRemove(v,'1'); 
if(a && b) {
  v.push_back('2'); 
}
retrurn ( a && b )l 
}
void WaysUpTheLadder(int n) {
// In  n adjacent objects , n-1 pairs of  immediate neighbor can be formed.  
//If I select any number pair of of these n-1 pairs , i get one way of climbing, 
//int no_of_ways = (n-1)C0 + (n-1)C1 + (n-2)C2 + ..... +(n-1)C(n-1) 

int no_of_ways = pow(2,n-1); 
vector<char> v(no_of_ways,'1'); 
bool moreones = true; 

while( moreones ) {
for ( auto x: v ) {

  do {
  
    for (int i = 0; i < v.size(); ++i){
      std::cout << v[i];
    }
   std::cout << "\n";
  
  }while(next_combination(begin(v),end(v)) ); 

}
moreones = Pop1sAndPushBack2(v); 

}

}
