#include "GraphFactory.h"
namespace GraphFactory
{

  void one_vertex_zero_edge_graph(int& V, int& E, vecVecI &adj)
  {
   
    E = 0;
    adj = {
      {}
    };
    V = (int)adj.size();
  }

  void one_vertex_self_edge_cyclic_graph(int& V, int& E, vecVecI &adj)
  {
    V = 1;
    E = 1;
    adj = {
      {0}
    };
    V = (int)adj.size();
  };

  void two_vertices_1_edge_dir_graph(int& V, int& E, vecVecI &adj) {}
  void two_vertices_2_edges_mutual_cycle_dir_graph(int& V, int& E, vecVecI &adj) {}

  void triangle_undir_graph(int& V, vecVecI& adj)
  {
    V = 3;
    adj = {
      {1,2},
    {0,2},
    {0,1}
    };
  }

  void v_shaped_undir_graph(int& V, vecVecI& adj)
  {
    V = 3;
    adj = {
    {1,2},
    {0},
    {0}
    };
  }


};