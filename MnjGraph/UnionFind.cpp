//Test status: WeightedQuickUnionUF_test() goood on 12/3/2022
#include "all_std.h" 
#include "GenericGraphHeader.h"

using vecI = std::vector<int>;
class WeightedQuickUnionUF
{
  vecI id;
  vecI sz;
  int count;
public:
  WeightedQuickUnionUF(int N)
  {
    count = N;
    //id.reserve(N);
    id.resize(N);
    sz.resize(N);
    for (int i = 0; i < N; ++i)
    {
      id[i] = i;
      sz[i] = 1;
    }
  }

  int get_count()
  {
    return count;
  }

  bool connected(int p,int q)
  {
    return find(p) == find(q);
  }

  int find(int p)
  {
    while (id[p] != p) p = id[p];
    return p;
  }

  void Union(int p,int q)
  {
    auto idi = find(p);
    auto idj = find(q);
    if (idi == idj)
      return;
    if (sz[idi] < sz[idj])
    {
      id[idi] = idj; 
      sz[idj] += sz[idi];
    }
    else
    {
      id[idj] = idi;
      sz[idi] += sz[idj];
    }
  }
};


void WeightedQuickUnionUF_test1()
{
 
  WeightedQuickUnionUF triangle(3);
  triangle.Union(0,1);
  triangle.Union(1, 2);
  triangle.Union(2, 1);

  auto count = triangle.get_count();
  auto connected31 = triangle.connected(0,1);
  auto parent_of_1 = triangle.find(1);
  auto parent_of_2 = triangle.find(2);
  assert(parent_of_1== parent_of_2);

  
}


void WeightedQuickUnionUF_test2()
{

  WeightedQuickUnionUF triangle_and_point(4);
  triangle_and_point.Union(0, 1);
  triangle_and_point.Union(1, 2);
  triangle_and_point.Union(2, 1);

  auto count = triangle_and_point.get_count();
  auto connected31 = triangle_and_point.connected(0, 1);
  auto parent_of_1 = triangle_and_point.find(1);
  auto parent_of_2 = triangle_and_point.find(2);
  assert(parent_of_1 == parent_of_2);

  //test: the 4th point is isolated
  auto parent_of_3 = triangle_and_point.find(3);
  assert(parent_of_1 != parent_of_3);
}

void WeightedQuickUnionUF_test() {
  WeightedQuickUnionUF_test1();
  WeightedQuickUnionUF_test2();
}