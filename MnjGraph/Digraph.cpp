//This is C++ version of Sedgewick's Algorithm's Data Type Digraph 
#include "all_std.h" 
#include "GenericGraphHeader.h"
#include "GraphFactory.h"

#include "Digraph.h"

Digraph::Digraph(int V)
  {
    this->V = V;
    this->E = 0;
    adj.resize(V);
    for (auto &x:adj)
    {
      vecI tmp;
      x = tmp;
    }
  }

Digraph::Digraph(vecVecI &iadj)
{
  E = 0;
  adj = iadj;
  for (auto& x : adj)
  {
    E += (int)x.size();
  }
  V = (int)adj.size();
}

  int Digraph::get_V() { return V; }
  int Digraph::get_E() { return E; }

  void Digraph::addEdge(int v, int w)
  {
    adj[v].emplace_back(w);
    E++;
  }

  vecI Digraph::get_adj(int v)
  {
    return adj[v];
  }

  Digraph Digraph::reverse()
  {
    Digraph dg(V);
    for (int v = 0 ; v< V;++v)
    {
      for (int w : adj[v])
      {
        dg.addEdge(w,v);
      }
    }
    return dg;
  }
