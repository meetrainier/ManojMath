#include "all_std.h" 
#include "GenericGraphHeader.h"
#include "GraphFactory.h"

#include "Digraph.h"

class DirectedCycle {

private: 
    vecB marked;
    vecI edgeTo;
    stack<int> cycle;
    vecB onStack;

    void dfs(Digraph &G, int v)
    {
      //The recursive call terminates (a) when isCycle() is true;
      //                              (b) when we have processed each vertex in the adjcency list of input v. 
      //                                  In other words, when we are done with the outer for loop. 
      //Q:How does a vertex gets add to the cycle? 
      //Ans: When it is marked and it is on stack. 
      marked[v] = true;
      onStack[v] = true;
      for (int& w : G.get_adj(v))
      {
        if (this->hasCycle())
          return;
        else if (!marked[w])
        {
          edgeTo[w] = v;
          dfs(G, w);
        }
        else if (onStack[w])
        {
          for (int x = v; x != w; x = edgeTo[x])
          {
            cycle.push(x);
          }
          cycle.push(w);
          cycle.push(v);
        }
        onStack[v] = false;
      }
    }

public:
    DirectedCycle(Digraph &G) 
    {
      //Note: the stack is not initialized. 
      auto V = G.get_V();

      marked.resize(V);
      edgeTo.resize(V);
      onStack.resize(V);

      for (int v = 0; v < V; ++v)
      {
        if (!marked[v])
          dfs(G,v);
      }
    }

    bool hasCycle()
    {
      return cycle.size();
    }

    stack<int> get_cycle()
    {
      return cycle;
    }
};


void test_hasCycle()
{
  //tbd:   - add a test case of self loop 
  //       -disconnected graph, one of them with loop.  
  //       - A graph with two loops. 
  int V; int E; vecVecI adj;
  GraphFactory::triangle_dir_graph(V, E, adj);
  Digraph dg(adj);
  //Digraph dg(V);
  //for (int i = 0; i < V; ++i)
  //{
  //  for (int j = 0; j < adj[i].size(); ++j)
  //  {
  //    dg.addEdge(i,adj[i][j]);
  //  }
  //}

  DirectedCycle dicycle(dg);
  auto c = dicycle.hasCycle();
  assert(c);

  Digraph dg_self_loop({{ 0 }});
  DirectedCycle dicycle_self_loop(dg_self_loop);
  auto c_self_loop = dicycle_self_loop.hasCycle();
  assert(c_self_loop);
}