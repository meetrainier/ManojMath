#include <algorithm> 
#include <cassert> 
#include <vector> 
#include "Modifying.h"
using VecI = std::vector<int>;
using VecC = std::vector<char>;
//bool is_even(int a)
//{
//  if (a % 2)
//    return false;
//  else
//    return true;
//}

int use_copy()
{
  return 0;
}
//Copy range of elements(function template)
int use_copy_n()
{
  VecI vec_i{1,2,3,4,5};
  VecI vec_i_copy(3);
  std::copy_n(std::begin(vec_i),3, std::begin(vec_i_copy));
  assert(1 == vec_i_copy[0]);
  assert(2 == vec_i_copy[1]);
  assert(3 == vec_i_copy[2]);
  return 0;
}
//Copy elements(function template)
int use_copy_if()
{
  VecI vec_i{ 1,2,3,4,5 };
  VecI vec_i_copy(3);
  std::copy_if(std::begin(vec_i), std::end(vec_i), 
               std::begin(vec_i_copy), is_even);
  assert(2 == vec_i_copy[0]);
  assert(4 == vec_i_copy[1]);  
  return 0;
}
//Copy certain elements of range(function template)
int use_copy_backward()
{
  //Note: 
  //1. The destination argument is an iterator that will be decremented. Hence pass end.
  //2. copy_backward() is not reverse_copy()
  
  //reverse_copy actually puts the elements in reverse order.

  //  1 2 3 4 5 - > 5 4 3 2 1
  //  copy_backward simply copies the elements backwards, but preserves their relative order.

  //  1 2 3 4 5
  //  5 is copied first, but put in the last spot.So your output is still :

  //1 2 3 4 5

  VecI vec_i{ 1,2,3,4,5 };
  VecI vec_i_copy(vec_i.size()+10);
  std::copy_backward(std::begin(vec_i), std::end(vec_i),
    std::end(vec_i_copy));
  assert(5 == vec_i_copy[4]);
  assert(4 == vec_i_copy[3]);
  return 0;
}
//Copy range of elements backward(function template)
int use_move()
{
  return 0;
}
//Move range of elements(function template)
int use_move_backward()
{
  return 0;
}
//Move range of elements backward(function template)
int use_swap()
{
  return 0;
}
//Exchange values of two objects(function template)
int use_swap_ranges()
{
  return 0;
}
//Exchange values of two ranges(function template)
int use_iter_swap()
{
  return 0;
}
//Exchange values of objects pointed to by two iterators(function template)
int use_transform()
{
  return 0;
}
//Transform range(function template)
int use_replace()
{
  return 0;
}
//Replace value in range(function template)
int use_replace_if()
{
  return 0;
}
//Replace values in range(function template)
//{
//  return 0;
//}
int use_replace_copy()
{
  return 0;
}
//Copy range replacing value(function template)
int use_replace_copy_if()
{
  return 0;
}
//Copy range replacing value(function template)
int use_fill()
{
  return 0;
}
//Fill range with value(function template)
int use_fill_n()
{
  return 0;
}
//Fill sequence with value(function template)
int use_generate()
{
  return 0;
}
//Generate values for range with function(function template)
int use_generate_n()
{
  return 0;
}
//Generate values for sequence with function(function template)
int use_remove()
{
  return 0;
}
//Remove value from range(function template)
int use_remove_if()
{
  return 0;
}
//Remove elements from range(function template)
int use_remove_copy()
{
  return 0;
}
//Copy range removing value(function template)
int use_remove_copy_if()
{
  return 0;
}
//Copy range removing values(function template)
int use_unique()
{
  return 0;
}
//Remove consecutive duplicates in range(function template)
int use_unique_copy()
{
  return 0;
}
//Copy range removing duplicates(function template)
int use_reverse()
{
  return 0;
}
//Reverse range(function template)
int use_reverse_copy()
{
  return 0;
}
//Copy range reversed(function template)
int use_rotate()
{
  return 0;
}
//Rotate left the elements in range(function template)
int use_rotate_copy()
{
  return 0;
}
//Copy range rotated left(function template)
int use_random_shuffle()
{
  return 0;
}
//Randomly rearrange elements in range(function template)
int use_shuffle()
{
  return 0;
}
//Randomly rearrange elements in range using generator(function template)

////Partitions:
//is_partitioned
////Test whether range is partitioned(function template)
//partition
////Partition range in two(function template)
//stable_partition
////Partition range in two - stable ordering(function template)
//partition_copy()
////Partition range into two(function template)
//partition_point
////Get partition point(function template)

//Sorting:
//sort
//Sort elements in range(function template)
//stable_sort
//Sort elements preserving order of equivalents(function template)
//partial_sort
//Partially sort elements in range(function template)
//partial_sort_copy
//Copy and partially sort range(function template)
//is_sorted
//Check whether range is sorted(function template)
//is_sorted_until
//Find first unsorted element in range(function template)
//nth_element()
////Sort element in range(function template)
//
////Binary search(operating on partitioned / sorted ranges) :
//  lower_bound
//  Return iterator to lower bound(function template)
//  upper_bound
//  Return iterator to upper bound(function template)
//  equal_range
//  Get subrange of equal elements(function template)
//  binary_search
//  Test if value exists in sorted sequence(function template)
//
