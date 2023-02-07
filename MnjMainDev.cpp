//
//copyright(c) 2009- 2022 Manoj Lnu 
//tbd: remove or move code so that main only contains the test method calls;
#include "all_std.h" 

#include "TestGeomUtils.h"
//#include "GeomUtils.h"
#include "TestMnjSmoother.h"
#include "MnjSmoothableSegment.h"
#include "MnjSmoothableLine.h"
#include "MnjSmoothableArc.h"
#include "TestMnjSmoother.h"
#include "MnjSudoku.h"
#include "MnjLine.h"
#include "boostGeometryExample.h"

using namespace std;


//class MnjSmoothableLine;
/**
//////////////////////////////////////////////////////////////////////////////////
// This function will obtain a reference to the parameter 'r' and increment it.
void f (int &r) { r++; }
// Template function.
template<class F, class P> void g (F f, P t) { f(t); }
int WrapperReference()
{
int i = 0 ;
g (f, i) ; // 'g<void (int &r), int>' is instantiated
// then 'i' will not be modified.
std::cout << i << std::endl; // Output -> 0
g (f, std::ref(i)); // 'g<void(int &r),reference_wrapper<int>>' is instantiated
// then 'i' will be modified.
std::cout << i << std::endl; // Output -> 1
return 0;
}
///////////////////////////////////////////////////////////////////////
class TestMnjLine {

public:
 void TestDeafultConstructor(){

  MnjLine l;
 }
// 
// 	MnjLine(){ }
//  MnjLine(const MnjLine &l){ 
//         startPoint = l.startPoint;
//         endPoint = l.endPoint;
//  }
//
//  MnjLine(Segment &iSeg1, Segment &iSeg2);
//	MnjLine(MnjPoint<double> &s,MnjPoint<double> &e);
////	SegmentType GetType(){ return SegmentType::LINE;}
//
//	void Set(MnjPoint<double> &s,MnjPoint<double> &e);
//	void GetStartPoint(MnjPoint<double> &p)const;
  

};
using vecI = std::vector<int>;
void print(vecI vec)
{
  for (auto& x : vec)
    cout << x << " ";
  cout << std::endl;
}

//void ShowPriorityQueueWorksOnVectorOfInts()
//{
//  vecI a{ 0, 1, 2};
//  vecI b{ -1, 1, 2 };
//  vecI c{ 1, 1, 2 };
//
//  std::priority_queue < vecI, std::vector<vecI>,  std::greater<vecI >> pq;
//  pq.push(a);
//  pq.push(b);
//  pq.push(c);
//
//  auto a1 = pq.top();
//  print(a1);
//  pq.pop();
//
//  auto b1 = pq.top();
//  print(b1);
//  pq.pop();
//
//  auto c1 = pq.top();
//  print(c1);
//}
extern  void DoesItHaveThePattern_test();



int find_substr(string substr, string str) {

  int postion = 0;
  auto beginning = str.c_str();
  int i = 0;
  char* p = (char *)beginning;
  //tbd while (p && '\0'!=p)
  {
  p = strstr(p, substr.c_str());
  //tbd if (!p)
   // break;
  cout << "A substring is at index:" << p - beginning << "\n";
  p++;
  };
  return 0;
}


void test()
{
  string substr, str;
  {
    substr = "ab"; str = "aabb";
    cout << "Finding " << substr << " in " << str << "\n";
    find_substr(substr, str);
    cout << "\n";
  }
  {
    substr = "ab"; str = "abab";
    find_substr(substr, str);
    cout << "\n";
  }
  {
    substr = "a"; str = "11111111111111111111111a";
    find_substr(substr, str);
    cout << "\n";
  }
}


/////
// C++ program to print subarray with sum as given sum

// Function to print subarray with sum as given sum
void subArraySum(int arr[], int n, int sum, pair<int,int> &pair_of_indices)
{
  // create an empty map
  unordered_map<int, int> map;

  // Maintains sum of elements so far
  int curr_sum = 0;

  for (int i = 0; i < n; i++) {
    // add current element to curr_sum
    curr_sum = curr_sum + arr[i];

    // if curr_sum is equal to target sum
    // we found a subarray starting from index 0
    // and ending at index i
    if (curr_sum == sum) {
      cout << "Sum found between indexes " << 0
        << " to " << i << endl;
      pair_of_indices = { 0 ,i };
      return;
    }

    // If curr_sum - sum already exists in map
    // we have found a subarray with target sum
    if (map.find(curr_sum - sum) != map.end()) {
      cout << "Sum found between indexes "
        << map[curr_sum - sum] + 1 << " to " << i
        << endl;
      pair_of_indices = { map[curr_sum - sum]+1 ,i};
      return;
    }

    map[curr_sum] = i;
  }

  // If we reach here, then no subarray exists
  cout << "No subarray with given sum exists";
}

// Driver code
int subArraySum_test()
{
  int arr[] = { 10, 2, -2, -20, 10 };
  int n = sizeof(arr) / sizeof(arr[0]);
  int sum = -10;

  // Function call
  pair<int, int> pair_of_indices;
  subArraySum(arr, n, sum, pair_of_indices);

  {
    int arr[] = {5, 10, 2, -2, -20, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = -10;

    // Function call
    pair<int, int> pair_of_indices;
    subArraySum(arr, n, sum, pair_of_indices);
  }

  return 0;
}


int subArraySumVersion2() {
  //int t;
  //cin >> t;
  bool foundanswer = false;

  //while (t--) {
  //while (1) {
  int n, s;
    cin >> n >> s;
    //cout << "N and S are " << n << " " << s << endl;

    int sum = 0;
    int startindex = 0;
    vector<int> values;

    for (int i = 0; i < n; i++) {

      int temp;
      cin >> temp;
      values.push_back(temp);
    }

    for (int i = startindex; i < n; i++) {
      sum = sum + values[i];
      //cout << "Value : " << values[i] << endl;

      if (sum > s) {
        startindex++;
        //cout << "Resetting... " << sum << endl;
        i = startindex - 1;
        sum = 0;
      }

      if (sum == s) {
        //cout << "Found." << endl;
        //for(int j=startindex; j<=i; j++) {
        //    cout << values[j] << " ";
        //}
        cout << startindex + 1 << " " << i + 1 << endl;
        foundanswer = true;
        break;
      }

    }
    if (foundanswer == false) {
      cout << -1 << endl;
    }
  //}
  return 0;
}

int subArraySumVersion3(int arr[], int n, int sum, std::pair<int,int> &pair_of_indices) {
  int cur_sum = arr[0];
  int start = 0;
  int i;
  for (i = 1; i < n; i++) {
    while (cur_sum > sum && start < i - 1) {
      cur_sum = cur_sum - arr[start];
      start++;
    }
    if (cur_sum == sum) {
      cout << "sum found between " << start << " and " << i - 1;
      pair_of_indices = {start,i-1};
      return 1;
    }
    if (i < n)
      cur_sum = cur_sum + arr[i];
  }
  cout << "sum  not found";
  return 0;
}

void subArraySumVersion3_test()
{
  {
    int arr[] = { 10, 2, -2, -20, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = -10;

    // Function call
    pair<int, int> pair_of_indices;
    subArraySumVersion3(arr, n, sum, pair_of_indices);
    assert(0 == pair_of_indices.first);
    assert(3 == pair_of_indices.second);
  }
  {
    int arr[] = { 5, 10, 2, -2, -20, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = -10;

    // Function call
    pair<int, int> pair_of_indices;
    subArraySumVersion3(arr, n, sum, pair_of_indices);
    
  }

}
/////////////////////////////////

//vector<vector<int>> uniquePerms(vector<int> arr, int n) {
//  // code here
//  
//  unordered_set<vector<int>> s;
//  
//  while (next_permutation(begin(arr), begin(arr) + n))
//  {
//    s.emplace(begin(arr), begin(arr) + n);
//  }
//  vector<vector<int>> vec(begin(s),end(s));
//  return vec;
//
//}


bool are_balanced_bracket(string x)
{
  stack<char> st;
  if (1 == (x.size() % 2))
    return false;

  for (auto& c : x)
  {
    if ('[' == c || '{' == c || '(' == c)
      st.push(c);
    else if (']' == c || '}' == c || ')' == c)
    {
      if (st.size())
      {
        auto c_tmp = st.top();
        if (c_tmp == '[' && c == ']')
          st.pop();
        else if (c_tmp == '{' && c == '}')
          st.pop();
        else if (c_tmp == '(' && c == ')')
          st.pop();
        else
          return false;
      }

    }
  }
  return (st.size() == 0);
  // Your code here
}
*/
///////////////////////////////////////////////////////
int main(int argc, char *argv[]){

  //subArraySumVersion3_test();
  //subArraySumVersion2();
  //subArraySum_test();
  //DoesItHaveThePattern_test();
  //test();
  /**
  ShowPriorityQueueWorksOnVectorOfInts();
  using iPair = std::pair<int, int>;
  std::vector<std::pair<int, iPair >> v;
  v.push_back({ 1,{1,1} });
  v.push_back({ 0, { 1,1 } });
  std::sort(begin(v),end(v));
  for (auto& x : v)
    cout << x.first << " " << std::endl;
    */
   //PointsInPolygon();
  //TestMnjLine testLine;

  //TestMnjSmoother<MnjSmoothableSegment,MnjSmoothableLine,MnjSmoothableArc> test;
  //sudoku_test1();
  
  //TestMnjSmoother test;
  //test.Test();
  
  //WrapperReference();
  
   //GeomUtils::TestGeomUtils::TestLineLineIntersect();  
   //TestGeomUtils test;
   //test.Test();
  return 0;
}
