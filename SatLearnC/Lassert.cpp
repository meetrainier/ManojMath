#include <cassert> 
#include <algorithm>
int add(int a, int b)
{
  return a + b;
}
int add_test()
{
  assert(5 == add(3, 2));
  assert(2 == add(0, 2));
  assert(1 == add(-1, 2));
  return 0;
}

int my_sort_test();

int main(char** argv, int argc)
{
  add_test();
  my_sort_test();
  return 0;
}

//
#include <vector>
int my_sort(std::vector<int> &vec)
{
  std::sort(std::begin(vec),std::end(vec));
  return 0;
}

int my_sort_test()
{
  std::vector vec1{3,2,1};
  my_sort(vec1);
  std::vector<int> v({ 1,2,3 });
  assert(vec1 == v);
  return 0;
}