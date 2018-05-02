#pragma once
//
extern bool is_even(int a);
//
extern int use_copy();

//Copy range of elements(function template)
extern int use_copy_n();//Copy first n elements
extern int use_copy_if();//Copy certain elements of range
extern int use_copy_backward();
//Copy range of elements backward(function template)
extern int use_move();
//Move range of elements(function template)
extern int use_move_backward();
//Move range of elements backward(function template)
extern int use_swap();
//Exchange values of two objects(function template)
extern int use_swap_ranges();
//Exchange values of two ranges(function template)
extern int use_iter_swap();
//Exchange values of objects pointed to by two iterators(function template)
extern int use_transform();
//Transform range(function template)
extern int use_replace();
//Replace value in range(function template)
extern int use_replace_if();
extern int use_replace_copy();
//Copy range replacing value(function template)
extern int use_replace_copy_if();
//Copy range replacing value(function template)
extern int use_fill();
//Fill range with value(function template)
extern int use_fill_n();
//Fill sequence with value(function template)
extern int use_generate();
//Generate values for range with function(function template)
extern int use_generate_n();
//Generate values for sequence with function(function template)
extern int use_remove();
//Remove value from range(function template)
extern int use_remove_if();
//Remove elements from range(function template)
extern int use_remove_copy();
//Copy range removing value(function template)
extern int use_remove_copy_if();
//Copy range removing values(function template)
extern int use_unique();
//Remove consecutive duplicates in range(function template)
extern int use_unique_copy();
//Copy range removing duplicates(function template)
extern int use_reverse();
//Reverse range(function template)
extern int use_reverse_copy();
//Copy range reversed(function template)
extern int use_rotate();
//Rotate left the elements in range(function template)
extern int use_rotate_copy();
//Copy range rotated left(function template)
extern int use_random_shuffle();
//Randomly rearrange elements in range(function template)
extern int use_shuffle();
//Randomly rearrange elements in range using generator(function template)

////Partitions:
//is_partitioned
////Test whether range is partitioned(function template)
//partition
////Partition range in two(function template)
//stable_partition
////Partition range in two - stable ordering(function template)
//partition_copy();
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
//nth_element();
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
