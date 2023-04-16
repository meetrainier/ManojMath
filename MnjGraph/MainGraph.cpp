#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>

using vecI = std::vector<int>;
using vecB = std::vector<bool>;
using vecVecI = std::vector<vecI>;
using vecI_PQ = std::priority_queue<vecI>;

void get_incident_edges(vecB& visited, int vertex, vecVecI edges, vecVecI& incident_edges)
{
	incident_edges.clear();
	for (auto& e : edges)
	{
		if (visited[e[0]] && visited[e[1]])
			continue;
		if (e[0] == vertex || e[1] == vertex)
			incident_edges.emplace_back(e);
	}
}

void add_incident_edges_to_pq(int vertex, vecB& visited, vecVecI& edges,vecI_PQ& pq)
{
	visited[vertex] = true;
	//int the_other = get_other 
	vecVecI incident_edges;
	get_incident_edges(visited,vertex, edges, incident_edges);
	for (auto& e : incident_edges)
		pq.push(e);
}



double Pr(int n, std::vector<vecI> edges,int s )
{
	double weight = 0;
  std::queue<int> mst;
  std::vector<bool> visited(n+1,false);
  vecI_PQ pq;
  visited[s] = true;
  auto v = s;
  add_incident_edges_to_pq(v,visited, edges, pq);
  while (!pq.empty())
  {
	  auto e = pq.top();
	  pq.pop();
	  if (visited[e[0]] && visited[e[1]])

		  continue;
	  weight += e[2];
      if(!visited[e[0]])
	    add_incident_edges_to_pq( e[0], visited, edges, pq);
	  if (!visited[e[1]])
		add_incident_edges_to_pq(e[1], visited, edges, pq);

  }
  return weight;
}

extern void is_cyclic_directed_test();
extern void is_cyclic_undirected_test();
//TestshortestChainLen(); 
void test_hasCycle();

int main() {
	//TestshortestChainLen(); 
	//is_cyclic_directed_test();
	//is_cyclic_undirected_test();
	test_hasCycle();

	return 0;
}
