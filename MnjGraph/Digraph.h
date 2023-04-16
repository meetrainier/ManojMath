#pragma once
//This is C++ version of Sedgewick's Algorithm's Data Type Digraph 
#include "all_std.h" 
#include "GenericGraphHeader.h"
#include "GraphFactory.h"

class Digraph {
private:
  int V;
  int E;

  vecVecI adj;
public:
  Digraph(int V);
  Digraph(vecVecI& iadj);
  int get_V();
  int get_E();

  void addEdge(int v, int w);

  vecI get_adj(int v);

  Digraph reverse();
};