#include "all_std.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */
using vecI = std::vector<int>;
bool operator >(vecI& v1, vecI& v2)
{
  return v1[2] > v2[2];
}

void add_to_pq(unordered_set<int> vertices_in_mst, vector<vector<int>>& edges, int vertex, std::priority_queue<vecI, vector<vecI>, std::greater<vecI>>& pq) {
  for (auto& x : edges)
  {
    auto it1 = vertices_in_mst.find(x[0]);
    auto it2 = vertices_in_mst.find(x[1]);
    bool already_present = (it1 != vertices_in_mst.end() && it2 != vertices_in_mst.end());//both vrtices are already visited. 
    if (!already_present)
    {
      if (x[0] == vertex || x[1] == vertex)
        pq.push(x);
    }
  }
}

int find_the_vertex_not_on_tree(priority_queue<vecI, vector<vecI>, std::greater<vecI>> &pq, unordered_set<int>& vertices_in_mst,  bool& eligible)
{
  auto e = pq.top();
  auto it1 = vertices_in_mst.find(e[0]);
  auto it2 = vertices_in_mst.find(e[1]);
  if (it1 != vertices_in_mst.end() && it2 == vertices_in_mst.end())
  {
    //pq.pop();
    eligible = 1;
    vertices_in_mst.insert(e[1]);
    return e[1];
  }
  else if (it1 == vertices_in_mst.end() && it2 != vertices_in_mst.end())
  {
   //pq.pop();
    eligible = 1;
    vertices_in_mst.insert(e[0]);
    return e[0];
  }
  else if (it1 != vertices_in_mst.end() && it2 != vertices_in_mst.end())//both vrtices are already visired. 
  {
    pq.pop();
    eligible = 0;
    return -1;
  }
  else if (it1 == vertices_in_mst.end() && it2 == vertices_in_mst.end())
  {
    assert(1);
    eligible = 0;
    return -1;
  }
  return -1;
}

void print(vector<int> v)
{
  for (auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

void print(std::priority_queue<vecI, vector<vecI>, std::greater<vecI>> pq)
{

  //std::vector<vecI> v(pq);
  //std::set<vecI> v(pq);
  //std::vector<vecI> v(std::start(pq),std::end(pq));
  auto pqTmp = pq;
  while (!pqTmp.empty())
  {
    print(pqTmp.top());
    pqTmp.pop();
  }
}

int CreatePQ(std::vector<vecI> edges, int vertex, std::priority_queue<vecI, std::vector<vecI>, std::greater<vecI>>& pq)
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
  auto it0 = std::find(begin(set_of_vert_at_mst), end(set_of_vert_at_mst), e[0]);
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

int TestPrims()
{
  //To creat eeasy test refer to : https://graphonline.ru/en/?q=en
  {
    std::vector<vecI> edges1{ {1,2,1},{1,3,2},{2,3,3} };
    auto w1 = prims(3, edges1, 1);
    assert(3 == w1);
  }
  {
    std::vector<vecI> edges2{ {1,2,1},
        {2,3,1},
        {3,4,1},
        {4,5,1},
        {5,1,1},

        {1,6,2},
        {2,6,3},
        {3,6,4},
        {4,6,5},
        {5,6,6},
    };
    auto w = prims(6, edges2, 1);
    assert(6 == w);
  }
  return 0;
}


int prims_main(int argc, char* argv[])
{

  std::string first_multiple_input_temp;

  //std::getline(cin, first_multiple_input_temp);
  ifstream ifile(argv[1]);
  std::getline(ifile, first_multiple_input_temp);
  //ifile.getline(first_multiple_input_temp);

  vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

  int n = stoi(first_multiple_input[0]);

  int m = stoi(first_multiple_input[1]);

  vector<vector<int>> edges(m);

  for (int i = 0; i < m; i++) {
    edges[i].resize(3);

    string edges_row_temp_temp;
    //getline(cin, edges_row_temp_temp);
    std::getline(ifile, edges_row_temp_temp);
    vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

    for (int j = 0; j < 3; j++) {
      int edges_row_item = stoi(edges_row_temp[j]);

      edges[i][j] = edges_row_item;
    }
  }

  string start_temp;
  //getline(cin, start_temp);
  std::getline(ifile, start_temp);

  int start = stoi(ltrim(rtrim(start_temp)));

  int result = prims(n, edges, start);
  //ofstream fout(getenv("OUTPUT_PATH"));
  //fout << result << "\n";
  //fout.close();

  return 0;
}

string ltrim(const string& str) {
  string s(str);

  s.erase(
    s.begin(),
    find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
  );

  return s;
}

string rtrim(const string& str) {
  string s(str);

  s.erase(
    find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
    s.end()
  );

  return s;
}

vector<string> split(const string& str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
