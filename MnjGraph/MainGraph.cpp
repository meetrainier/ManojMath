#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>

using vecI = std::vector<int>;
/*
int CreatePQ(std::vector<vecI> edges, int vertex, std::priority_queue<vecI,std::vector<vecI>, std::greater<vecI>>& pq)
{
    for (auto& e : edges)
    {
        if (e[0] == vertex || e[1] == vertex)
            pq.push(e);
    }
    return 0;
}

int FindTheOtherVertex(vecI e, std::unordered_set<int> set_of_vert_at_mst)
{
    auto it0 = std::find(begin(set_of_vert_at_mst),end(set_of_vert_at_mst),e[0]);
    if (it0 == end(set_of_vert_at_mst))
        return e[0];
    auto it1 = std::find(begin(set_of_vert_at_mst), end(set_of_vert_at_mst), e[1]);
    if (it0 == end(set_of_vert_at_mst))
        return e[1];
    return -1;
}

bool IsEligible(vecI e, std::unordered_set<int> set_of_vert_at_mst)
{
    auto it0 = set_of_vert_at_mst.find(e[0]);
    auto it1 = set_of_vert_at_mst.find(e[1]);
    auto theEnd = set_of_vert_at_mst.end();
    return !(it0 != theEnd && it1 != theEnd);
}

int prims(int n, std::vector<vecI> edges, int s)
{
    //1. Take a vertex(start with source)
    //    2. Find all edged incident on it.
    //    2.1 find the edge with min - weight.If the set of edges is empty, start with any remaining vertex . else terminate.
    //    2.2 check if the edge is already used
    //    2.3 if not used, mark it.Find the other vertex.Go to step 1.
    //    if used go to step 2.1

    std::vector<bool> edge_state(edges.size(), false);
    std::priority_queue<vecI, std::vector<vecI>, std::greater<vecI>> pq;
    int vertex = s;
    std::unordered_set<int> set_of_vert_at_mst;
    int weight = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        set_of_vert_at_mst.insert(vertex);
        CreatePQ(edges, vertex, pq);
        vecI current_e;
        while (!pq.empty())
        {
            
            current_e = pq.top();
            pq.pop();
            if (IsEligible(current_e, set_of_vert_at_mst))
            {
                weight += current_e[2];
                break;
            }

        };
        vertex = FindTheOtherVertex(current_e, set_of_vert_at_mst);
        //assert(-1 != vertex);
    }
    return weight;
}
*/

int main() {

	//TestshortestChainLen(); 
	return 0; 
}
