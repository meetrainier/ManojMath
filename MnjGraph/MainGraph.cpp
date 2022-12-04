#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>

using vecI = std::vector<int>;
extern void prims_from_doc_test();
extern void WeightedQuickUnionUF_test();

int main() {
	prims_from_doc_test();
	WeightedQuickUnionUF_test();

	//TestshortestChainLen(); 
	return 0; 
}
