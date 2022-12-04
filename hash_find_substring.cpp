#include "all_std.h"
bool DoesItHaveThePattern(std::string& t, std::string & p)
{
  auto t_length = t.size();
  auto p_length = p.size();
  //compute hash of p 
  std::hash<std::string>  hasher;
  auto p_hash = hasher(p);
  for (size_t i = 0; i < t_length - p_length +1; ++i)
  {
    std::string tmp_str(begin(t) + i, begin(t) + i + p_length);
    auto t_sub_str_hash = hasher(tmp_str);
    if (t_sub_str_hash == p_hash)
      return true;
  }
  return false;
}


void DoesItHaveThePattern_test()
{
  std::string t, p;

  //Test 1:
  {
    t = "abcd";
    p = "bc";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 2 :
  { 
    t = "abcd";
    p = "ab";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 3 :
  {
    t = "abcd";
    p = "cd";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  // Test 4 :
  {
    t = "abcd";
    p = "a";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 5 :
  {
    t = "abcd";
      p = "c";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 6 :
  {
    t = "abcd";
    p = "d";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 7 :
  {
    t = "abcd";
    p = "abcd";
    auto result = DoesItHaveThePattern(t, p);
    assert(true == result);
  }

  //Test 8:
  {
    t = "abcd";
    p = "af";
    auto result = DoesItHaveThePattern(t, p);
    assert(false == result);
  }

}

