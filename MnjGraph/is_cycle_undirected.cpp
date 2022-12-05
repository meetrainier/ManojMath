#include "all_std.h" 
#include "GenericGraphHeader.h"
#include "GraphFactory.h"



bool dfs(vecVecI graph, int src, int parent, vecB& visited) {
  ///mark the visited vertices 
  visited[src] = true;
  //call the neighbours
  for (int nbr : graph[src]) {
    //cycle means nbr is already visited but nbr of src is not be a parent
    if (visited[nbr] == true && nbr != parent) {
      return true;
    }
    else if (visited[nbr] == false) {
      //call dfs
      auto val = dfs(graph, nbr, src, visited);
      if (val)return true;
    }
  }
  return false;
}

bool is_cyclic_undirected(int V, vecVecI adj) {
  //create a boolean visited array to track the record of visited elements
  vecB visited(V,false);
  //call dfs for all non-visited vertices
  for (int i = 0; i < V; i++) {
    if (visited[i] == false) {
      int parent = -1;
      if (dfs(adj, i, parent, visited)) {
        return true;
      }
    }
  }
  return false;
}

void is_cyclic_undirected_test1()
{
  int V; 
  vecVecI adj;
  GraphFactory::triangle_undir_graph( V, adj);
  auto cycle = is_cyclic_undirected(V,adj);
  assert(cycle);
}

void is_cyclic_undirected_test2()
{
  int V;
  vecVecI adj;
  GraphFactory::v_shaped_undir_graph(V, adj);
  auto cycle = is_cyclic_undirected(V, adj);
  assert(!cycle);
}
void is_cyclic_undirected_test()
{
  is_cyclic_undirected_test1();
  is_cyclic_undirected_test2();
}