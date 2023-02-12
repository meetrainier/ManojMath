#include "all_std.h" 
#include "GenericGraphHeader.h"
#include "GraphFactory.h"

//class Solution {
  // Function to detect cycle in a directed graph.
//public:
  bool is_cyclic_directed(int V, vecVecI adj) {
    //we use kahn's algorithm

    //firstly we find the indegree of all vertices
    //int[] indegree = new int[V];
    vecI indegree(V);
    //for (ArrayList<Integer> list : adj) {
    for (auto& list : adj) {
      for (int v : list) {
        indegree[v]++;
      }
    }
    //we use bfs for topological sort
    //so we create a queue
    queue<int> q;;
    //push all the vertices which indegree =0 in the queue
    for (int v = 0; v < V; v++) {
      if (indegree[v] == 0) {
        q.push(v);
      }
    }
    //do bfs
    int count = 0;
    while (q.size() > 0) {
      //remove
      int vertex = q.front();
      cout << "removed from q" << vertex << endl;
      q.pop();
      //work
      count++;
      //update the indegree of the neighbours of vertex(because we remove their parent)
      for (int nbr : adj[vertex]) {
        indegree[nbr]--;
        //add the vertex which indegree =0
        if (indegree[nbr] == 0) {
          q.push(nbr);
        }
      }
    }
    //if count is equal to V,then it is not cyclic

    if (count == V) {
      return false;
    }
    return true;
  }

 void is_cyclic_directed_test1()
  {
   int V = 5;
   vecVecI adj{
     {1,2},
     {},
     {3},
     {4},
     {2}
   };

   bool res = is_cyclic_directed(V,adj);
   assert(true==res);
 }

 void is_cyclic_directed_test2()
 {
   int V = 5;
   vecVecI adj{
     {1,2},
     {},
     {3},
     {4},
     {}
   };

   bool res = is_cyclic_directed(V, adj);
   assert(false == res);
 }

 void is_cyclic_directed_test3()
 {
   //int V = 1;
   //vecVecI adj{
   //  {}
   //};
   int V, E;
   vecVecI adj;
   GraphFactory::one_vertex_zero_edge_graph(V,E,adj);
   bool res = is_cyclic_directed(V, adj);
   assert(false == res);
 }

 void is_cyclic_directed_test4()
 {
   int V, E;
   vecVecI adj;
   GraphFactory::one_vertex_self_edge_cyclic_graph(V, E, adj);
   bool res = is_cyclic_directed(V, adj);
   assert(true == res);
 }
 void is_cyclic_directed_test()
 {
   is_cyclic_directed_test1();
   is_cyclic_directed_test2();
   is_cyclic_directed_test3();
   is_cyclic_directed_test4();
 }
