/******************************************************************************
//
//copyright(c) 2009- 2022 Manoj Lnu
*******************************************************************************/
//Implementation of Runa -karp algorithm 
//Test status: find_sub_strings_test() goood on 12/3/2022
#include <iostream>
#include <string>
#include <cassert>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

int compute_hash(string str, int q, int d)
{
  int t = 0;
  for (size_t i = 0; i < str.length(); ++i)
  {
    t = (d * t + str[i]) % q;
  }
  return t;
}
//////////////////////////////////////
vector<int> find_sub_strings(string txt, string pat, int d)
{
  //d = size of alphabets

  int debug = 0;

  vector<int> vec;
  int q = INT_MAX;
  int h = 1;

  int M = (int)pat.length();
  auto N = txt.length();

  int  m = compute_hash(pat, q, d);
  if (debug)
    cout << "m=" << m << endl;
  string first_substr(begin(txt), begin(txt) + M);
  int  t = compute_hash(first_substr, q, d);

  if (debug)
  {
    int hq = ((int)pow(d, M - 1)) % q;
    cout << "hq=" << hq << endl;
    int hComputed = ((int)pow(d, M - 1));
    cout << "hComputed=" << hComputed << endl;
  }

  for (int i = 0; i < M - 1; i++)
    h = (h * d) % q;

  if (debug)
  {
    cout << "h=" << h << endl;
    cout << "M=" << M << endl;
  }

  for (size_t i = 0; i <= N - M; ++i)
  {
    if (t == m)
    {
      if (debug)
      {
        cout << "t and m are equal." << endl;
      }
      //if rigorous comparison succeeds,  
      //store the index to return;
      string str_tmp(begin(txt) + i, begin(txt) + i + M);
      if (debug)
      {
        cout << "str_tmp" << str_tmp << endl;
      }
      if (str_tmp == pat)
      {
        vec.emplace_back(i);
      }
    }

    if (i < N - M)
    {
      t = (d * (t - h * txt[i]) + txt[i + M]) % q;
      if (t < 0)
        t = t + q;
    }
    if (debug)
    {
      cout << "i=" << i << endl;
      cout << "t=" << t << endl;
    }
  }
  return vec;
}

int find_sub_strings_test()
{
  int debug = 0;
  int d = 256;//number of chars in alphabets 

  {
    auto vec1 = find_sub_strings("aabb", "ab", d);
    if (debug)
    {
      for (auto& x : vec1)
        cout << "Substring found at " << x << endl;
    }
    assert(1 == vec1[0]);
  }

  {
    auto vec2 = find_sub_strings("abab", "ab", d);
    if (debug)
    {
      for (auto& x : vec2)
        cout << "Substring found at " << x << endl;
    }
    assert(0 == vec2[0]);
  }

  {
    auto vec3 = find_sub_strings("11a", "a", d);

    if (debug)
    {
      for (auto& x : vec3)
        cout << "Substring found at " << x << endl;
    }
    assert(2 == vec3[0]);
  }
  return 0;
}