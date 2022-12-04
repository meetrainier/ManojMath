//Test status: prims_from_doc_test() goood on 12/3/2022
#include <limits> 
#include <map>
#include <queue> 
#include <vector> 
#include <cassert> 

using vecI = std::vector<int>;
using vecB = std::vector<bool>;

using vecVecI = std::vector<vecI>;
//using PQvecI = std::priority_queue<vecI,vecVecI,std::greater<vecI>>;

class Edge
{
  int v1, v2;
  double weight;
public:
  Edge(int iv1, int iv2, double iweight)
  {
    v1 = iv1;
    v2 = iv2;
    weight = iweight;
  }
  int either() { return v1; }
  int other(int vertex) {
    if (vertex == v1) return v2;
    else if (vertex == v2) return v1;
    else { return -999999; }
  }
  double get_weight()
  {
    return weight;
  }
};

using vecEdge = std::vector<Edge>;

bool operator>(Edge e1, Edge e2)
{
  return e1.get_weight() > e2.get_weight();
}
using PQEdge = std::priority_queue<Edge, vecEdge, std::greater<Edge>>;

class Graph
{
public:
  int V;
  std::map<int, vecEdge> v_to_e;

  Graph(int n, vecVecI adj)
  {
    V = n;
    for (auto& x : adj)
    {
      double w = x[2];
      Edge edge(x[0], x[1], w);
      if (v_to_e.find(x[0]) != v_to_e.end())
        v_to_e[x[0]].emplace_back(edge);
      else
      {
        vecEdge v_tmp({ edge });
        v_to_e[x[0]] = v_tmp;
      }
    }
  }

};

void visit(Graph& G, int vertex, vecB& visited, PQEdge &pq)
{
  visited[vertex] = true;
  for (auto& e : G.v_to_e[vertex])
  {
    auto v1 = e.either();
    if (visited[v1] && visited[e.other(v1)])
      continue;
    pq.push(e);
  }
}

double prims_from_doc(int n, vecVecI edges, int s)
{
  //Prepare Graph 
  Graph G(n, edges);
  //init 
  vecB visited(n+1, false);
  std::queue<Edge> mst;
  PQEdge pq;
  int vertex = s;
  //visited[vertex] = true;
  visit(G, vertex, visited, pq);
  double weight = 0;
  while (!pq.empty())
  {
    auto e = pq.top();
    pq.pop();
    auto v1 = e.either();
    if (visited[v1] && visited[e.other(v1)])
      continue;
    weight += e.get_weight();
    if (!visited[v1])
      visit(G, v1, visited, pq);
    if (!visited[e.other(v1)])
      visit(G, e.other(v1), visited, pq);
  };

  return weight;
}

void  prims_from_doc_test()
{
  {
    int n = 3; int s = 1;
    vecVecI edges
    {
      {1,2,1},
      {1,3,2},
      {2,3,3}
    };
    auto weight = prims_from_doc(n, edges, s);
    assert(3.0==weight);
  }

  {
    int n = 6; int s = 1;
    vecVecI edges
    {
      {1,2,1},
      {2,3,1},
      {3,4,1},
      {4,5,1},
      {5,1,1},

      {1,6,2},
      {2,6,2},
      {3,6,3},
      {4,6,4},
      {5,6,5},

    };
    auto weight = prims_from_doc(n, edges, s);

    assert(6.0 == weight);
  }


}
